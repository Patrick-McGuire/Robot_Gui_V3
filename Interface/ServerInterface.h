#ifndef ROBOT_GUI_V3_SERVERINTERFACE_H
#define ROBOT_GUI_V3_SERVERINTERFACE_H
#include "BaseInterface.h"
#include <memory>
#include <QTcpServer>
#include <QDebug>
#include "../WidgetData.h"
#include "../GuiInstance.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "DataInput.h"
#include "../CoreGui.h"

class CoreGui;

class ServerInterface : public QTcpServer, public BaseInterface {
Q_OBJECT
public:
    explicit ServerInterface(QObject *parent, int _port);

    void setWidgetData(WidgetData *_widgetData) override;

    void startServer();

public slots:
    void incomingConnection();

    void receiveData();

signals:
    void newData();

private:
    DataInput *dataInput;
    int port;

};


#endif //ROBOT_GUI_V3_SERVERINTERFACE_H
