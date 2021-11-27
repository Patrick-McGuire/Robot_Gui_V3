#ifndef ROBOT_GUI_V3_LOCALSERVER_H
#define ROBOT_GUI_V3_LOCALSERVER_H
#include <memory>
#include <QTcpServer>
#include <QDebug>
#include "../WidgetData.h"
#include "../RobotGUI.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

class RobotGUI;     // Fixes some reference errors

/**
 * @class LocalServer
 * Server that the GUI recives data from
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class LocalServer :  public QTcpServer {
Q_OBJECT
public:
    /**
     * Constructor
     * @param parent QObject to make parent
     * @param widgetData global WidgetData object to update when new data is received
     * @param robotGui RobotGUI object to connect slots
     */
    explicit LocalServer(QObject *parent, WidgetData *widgetData, RobotGUI *robotGui);

    /**
     * Opens the server
     */
    void StartServer();

signals:
    /**
     * emitted when new data is received and processed
     */
    void newData();

public slots:
    /**
     * New connection
     */
    void incomingConnection();

    /**
     * Receive data from a client and process it
     */
    void receiveData();

private:
    WidgetData *_widgetData;
    RobotGUI *_robotGui;
    char *dataString;

    /**
     * @bug overwrites existing json structs instead of writing to them
     *
     * parses a json value object into the internal json struct format
     * @param value rapidjson value object to parse
     * @return custom json struct
     */
    static void parseArray(rapidjson::Value *value, WidgetData::internalJSON_ptr json);

    static std::string getOutputJson(ReturnType returnType);
};

#endif //ROBOT_GUI_V3_LOCALSERVER_H
