#include "ServerInterface.h"
#include "iostream"
#include "../WidgetData.h"
#include <QTcpSocket>
#include <vector>

ServerInterface::ServerInterface(QObject *parent, int _port) : QTcpServer(parent), BaseInterface() {
    dataInput = nullptr;
    port = _port;
}

ServerInterface::~ServerInterface() {
    delete dataInput;
}

void ServerInterface::setWidgetData(RobotGui::WidgetData *_widgetData) {
    BaseInterface::setWidgetData(_widgetData);
    dataInput = new DataInput(getWidgetData());
    output->mapSet("Flags", getWidgetData()->getFlagOutput());
    output->mapSet("Values", getWidgetData()->getOutputJson());
}

void ServerInterface::startServer() {
    if (!this->listen(QHostAddress::Any, port)) {
        qDebug("Could not start server");
    } else {
        connect(this, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
        qDebug("Listening...");
    }
}

void ServerInterface::incomingConnection() {
    QTcpSocket *socket = this->nextPendingConnection();
    if (!socket)
        return;
    qDebug("Client connected");
    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

void ServerInterface::receiveData() {
    auto *senderObj = dynamic_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = senderObj->readAll();

    dataInput->parse((char *) data.data(), data.length());        // Parse the data
    // Check if we received any data
    if (getWidgetData()->keyUpdated()) {
        emit newData();
    }
    senderObj->write(output->toString().c_str());
}


