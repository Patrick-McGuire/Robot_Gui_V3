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
        std::cout << "Could not start server\n";
    }
    else {
        connect(this, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
        std::cout << "Listening...\n";
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
    auto *sender = dynamic_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = sender->readAll();

    if(data.length() > 5) {
        // Get the data about the message
        int id = (int) data.at(0);
        lengthConverter msgLength = {0};
        msgLength.in[0] = (uint8_t) data.at(1);
        msgLength.in[1] = (uint8_t) data.at(2);
        msgLength.in[2] = (uint8_t) data.at(3);
        msgLength.in[3] = (uint8_t) data.at(4);
        data.remove(0, 5);

        // Get a byte vector
        const unsigned char *begin = reinterpret_cast<unsigned char *>(data.data());
        const unsigned char *end = begin + data.length();
        std::vector<char> bufferToCompress(begin, end);
        bufferToCompress.resize(msgLength.length, 0);       // Limit to the size of the message,

        // Different types of messages
        if (id == customJSONMessage) {
            std::string jsonString(bufferToCompress.begin(), bufferToCompress.end());
            char jsonCstring[jsonString.length() + 1];
            std::strcpy(jsonCstring, jsonString.c_str());
            rapidjson::Document doc;
            doc.Parse(jsonCstring);
            rapidjson::Value::MemberIterator M;

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
                }
            }

        } else if (id == customIMGMessage) {
            try {
                cv::Mat img = cv::imdecode(bufferToCompress, cv::IMREAD_ANYCOLOR);
                cv::imshow("HIF", img);
                if (cv::waitKey(10) == 27) {}
            } catch (cv::Exception) {
                std::cout << "CVERROR\n";
            }
        }
        emit newData();
    }
}
