#ifndef ROBOT_GUI_V3_LOCALSERVER_H
#define ROBOT_GUI_V3_LOCALSERVER_H

#include <QTcpServer>
#include <QDebug>
#include "../WidgetData.h"

class LocalServer : public QTcpServer {
Q_OBJECT

public:
    explicit LocalServer(QObject *parent, WidgetData *widgetData);
    /**
     * Opens the server
     */
    void StartServer();

signals:

public slots:
    void incomingConnection();
    void newData();

private:
    WidgetData *_widgetData;
};


#endif //ROBOT_GUI_V3_LOCALSERVER_H
