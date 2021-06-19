#include "LocalServer.h"
#include "iostream"
#include <QTcpSocket>
#include "opencv2/opencv.hpp"
#include <vector>
#include "../Constants.h"

LocalServer::LocalServer(QObject *parent, WidgetData *widgetData) : QTcpServer(parent) {
    _widgetData = widgetData;
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

    connect(socket, SIGNAL(readyRead()), this, SLOT(newData()));
}


void LocalServer::newData() {
    auto* sender = dynamic_cast<QTcpSocket*>(QObject::sender());
    QByteArray data = sender->readAll();

    const unsigned char* begin = reinterpret_cast<unsigned char*>(data.data());
    const unsigned char* end = begin + data.length();
    std::vector<char> bufferToCompress( begin, end );

    // Determine message type
    int id = (unsigned char) bufferToCompress[0];
    bufferToCompress.erase(bufferToCompress.begin());
    if(id == customJSONMessage) {

    } else if(id == customIMGMessage) {
        try {
            cv::Mat img = cv::imdecode(bufferToCompress, cv::IMREAD_ANYCOLOR);
            cv::imshow("HIF", img);
            if(cv::waitKey(10) == 27 ) {}
        } catch(cv::Exception) {
            std::cout << "CVERROR\n";
        }
    }


}

//    for (int index = 0; index < bufferToCompress.size(); ++index) {
//        if(bufferToCompress[index] == 60 && bufferToCompress[index+1] == 69 && bufferToCompress[index+2] == 78 && bufferToCompress[index+3] == 68 && bufferToCompress[index+4] == 62) {
//            bufferToCompress.resize(index);
//            break;
//        }
//    }
//    for (int index = 0; index < bufferToCompress.size(); ++index) {
//        std::cout << bufferToCompress[index];
//        std::cout << "\n";
//    }
