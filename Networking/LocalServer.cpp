#include "LocalServer.h"
#include "iostream"
#include <QTcpSocket>
#include "opencv2/opencv.hpp"
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

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
        auto id = static_cast<MessageType>((int) data.at(0));
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
                for (rapidjson::Value::MemberIterator M = doc.MemberBegin(); M != doc.MemberEnd(); M++) {
                    std::string keyName = M->name.GetString();
                    _widgetData->setJSON(keyName, parseArray(&doc[keyName.data()]));
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

WidgetData::internalJSON_ptr LocalServer::parseArray(rapidjson::Value *value) {
    auto rtn = std::make_shared<WidgetData::internalJSON>();
    rtn->type = WidgetData::vector_t;

    if(value->IsBool()) {
        rtn->boolVal = value->GetBool();
        rtn->type = WidgetData::bool_t;
    } else if(value->IsInt()) {
        rtn->intVal = value->GetInt();
        rtn->type = WidgetData::int_t;
    } else if(value->IsDouble()) {
        rtn->doubleVal = value->GetDouble();
        rtn->type = WidgetData::double_t;
    } else if(value->IsString()) {
        rtn->stringVal = value->GetString();
        rtn->type = WidgetData::string_t;
    } else if(value->IsArray()) {
        rtn->type = WidgetData::vector_t;
        auto array = value->GetArray();
        int count = 0;
        for (rapidjson::Value::ConstValueIterator itr = array.Begin(); itr != array.End(); ++itr, count++) {
            rtn->vector.push_back(parseArray(&array[count]));
        }
    } else if(value->IsObject()) {
        rtn->type = WidgetData::map_t;
        auto obj = value->GetObject();
        rapidjson::Value::MemberIterator M;
        for (M = obj.MemberBegin(); M != obj.MemberEnd(); M++) {
            rtn->map[M->name.GetString()] = parseArray(&obj[M->name]);
        }
    }
    return rtn;
}
