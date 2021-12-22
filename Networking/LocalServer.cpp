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
    dataInput = new DataInput(_widgetData, DataInput::CUSTOM_MSG_FORMAT);
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
    // Read all the data from the socket
    auto *senderObj = dynamic_cast<QTcpSocket*>(QObject::sender());
    QByteArray data = senderObj->readAll();

    dataInput->parse((char*)data.data(), data.length());        // Parse the data

    // Check if we received any data
    if(_widgetData->keyUpdated()) {
        std::cout << "adsf\n";
        emit newData();
    }
}

void LocalServer::parseArray(rapidjson::Value *value, WidgetData::internalJSON_ptr json) {
    if(value->IsBool()) {
        json->boolVal = value->GetBool();
        json->type = WidgetData::bool_t;
    } else if(value->IsInt()) {
        json->intVal = value->GetInt();
        json->type = WidgetData::int_t;
    } else if(value->IsDouble()) {
        json->doubleVal = value->GetDouble();
        json->type = WidgetData::double_t;
    } else if(value->IsString()) {
        json->stringVal = value->GetString();
        json->type = WidgetData::string_t;
    } else if(value->IsArray()) {
        json->type = WidgetData::vector_t;
        auto array = value->GetArray();
        int count = 0;
        for (rapidjson::Value::ConstValueIterator itr = array.Begin(); itr != array.End(); ++itr, count++) {
            WidgetData::internalJSON_ptr eleJson;
            if(count < json->vector.size()) {
                eleJson = json->vector[count];
            } else {
                eleJson = std::make_shared<WidgetData::internalJSON>();
                json->vector.push_back(eleJson);
            }
            parseArray(&array[count], eleJson);
        }
        while (json->vector.size() > count) {
            json->vector.pop_back();
        }
    } else if(value->IsObject()) {
        json->type = WidgetData::map_t;
        auto obj = value->GetObject();
        rapidjson::Value::MemberIterator M;
        for (M = obj.MemberBegin(); M != obj.MemberEnd(); M++) {
            std::string name = M->name.GetString();
            WidgetData::internalJSON_ptr eleJson;
            if(json->map.count(name) != 0) {
                eleJson = json->map[name];
            } else {
                eleJson = std::make_shared<WidgetData::internalJSON>();
                json->map[name] = eleJson;
            }
            parseArray(&obj[M->name], eleJson);
        }
    }
}

void LocalServer::writeOutData(ReturnType returnType, QTcpSocket* socket) {
    rapidjson::Document doc;
    doc.SetObject();

    // Create the json output
    rapidjson::Value flags("Flags", 5, doc.GetAllocator());
    rapidjson::Value flagsValue;
    flagsValue.SetObject();
    for(auto & i : *_widgetData->getFlagOutput()) {
        rapidjson::Value newVal(i.first.c_str(), i.first.size(), doc.GetAllocator());
        flagsValue.AddMember(newVal, i.second, doc.GetAllocator());
    }
    doc.AddMember(flags, flagsValue, doc.GetAllocator());

    // Write to string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    socket->write(buffer.GetString());
}


