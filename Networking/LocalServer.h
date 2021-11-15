#ifndef ROBOT_GUI_V3_LOCALSERVER_H
#define ROBOT_GUI_V3_LOCALSERVER_H
#include <memory>
#include <QTcpServer>
#include <QDebug>
#include "../WidgetData.h"
#include "../RobotGUI.h"

class RobotGUI;

class LocalServer :  public QTcpServer {
Q_OBJECT

public:
    explicit LocalServer(QObject *parent, WidgetData *widgetData, RobotGUI *robotGui);
    /**
     * Opens the server
     */
    void StartServer();

signals:
    void newData();

public slots:
    void incomingConnection();
    void receiveData();

private:
//    std::shared_ptr<WidgetData> widgetData;
    WidgetData *_widgetData;
    RobotGUI *_robotGui;
    char *dataString;
};


#endif //ROBOT_GUI_V3_LOCALSERVER_H
