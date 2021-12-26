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
        emit newData();
    }
    writeOutData(None, senderObj);
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

