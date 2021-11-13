#include "LocalServer.h"
#include "iostream"
#include <QTcpSocket>
#include "opencv2/opencv.hpp"
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
//192.168.0.8

union lengthConverter {
    std::int32_t length;
    std::uint8_t in[4];
};

LocalServer::LocalServer(QObject *parent, WidgetData *widgetData, RobotGUI *robotGui) : QTcpServer(parent) {
    _widgetData = widgetData;
    _robotGui = robotGui;
    connect(this, SIGNAL(newData()), _robotGui, SLOT(updateGUI()));
}

void LocalServer::StartServer() {
    if(!this->listen(QHostAddress::Any,1254)) {
        qDebug("Could not start server");
    }
    else {
        connect(this, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
        qDebug("Listening...");
    }
}

void LocalServer::incomingConnection() {
    QTcpSocket *socket = this->nextPendingConnection();
    if (!socket)
        return;
    qDebug("Client connected");
    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
}


void LocalServer::receiveData() {
    auto *sender = dynamic_cast<QTcpSocket*>(QObject::sender());
    QByteArray data = sender->readAll();

    if(data.length() > 6) {
        // Get the data about the message
        auto id = static_cast<messageType>((int) data.at(0));
        lengthConverter msgLength{};
        msgLength.in[0] = (uint8_t) data.at(1);
        msgLength.in[1] = (uint8_t) data.at(2);
        msgLength.in[2] = (uint8_t) data.at(3);
        msgLength.in[3] = (uint8_t) data.at(4);
        auto outputCode = (uint8_t) data.at(5);
        auto imgId = (uint8_t) data.at(6);          // only used by img
        data.remove(0, 6);

        if(msgLength.length < 0 || data.length() < msgLength.length) {          // Int overflow, message corrupted
            return;
        }

        dataString = (char*)(data.data());
        dataString[msgLength.length] = (char) 0;

        // Different types of messages
        switch (id) {
            case JSON: {
                rapidjson::Document doc;
                doc.Parse(dataString);
                rapidjson::Value::MemberIterator M;
                // Iterate though all json keys and save their values to widgetData
                for (M = doc.MemberBegin(); M != doc.MemberEnd(); M++) {
                    std::string keyName = M->name.GetString();
                    char keyNameCString[20];
                    std::strcpy(keyNameCString, keyName.c_str());
                    if (doc[keyNameCString].IsString()) {
                        _widgetData->setString(keyNameCString, doc[keyNameCString].GetString());
                    } else if (doc[keyNameCString].IsDouble()) {
                        _widgetData->setDouble(keyNameCString, doc[keyNameCString].GetDouble());
                    } else if (doc[keyNameCString].IsInt()) {
                        _widgetData->setInt(keyNameCString, doc[keyNameCString].GetInt());
                    } else if(doc[keyNameCString].IsBool()) {
                        _widgetData->setBool(keyNameCString, doc[keyNameCString].GetBool());
                    }
                }
                break;
            } case IMG: {
                try {
                    // Decode the image and save it to widgetData
                    auto imgIdStr = std::to_string(imgId);
                    _widgetData->setImg(imgIdStr, cv::imdecode(cv::Mat(1, msgLength.length+1, CV_8UC1, dataString+1), cv::IMREAD_ANYCOLOR));
                } catch (cv::Exception const &e) {
                    // You sent a bad img
                    std::cout << "CVERROR\n";
                }
                break;
            } default: {
                return;         // We don't need to emit new data if we don't have new data
            }
        }
        emit newData();         // This will cause the function that updates all widgets to run
    }
}
