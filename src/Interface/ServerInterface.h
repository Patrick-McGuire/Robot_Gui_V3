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
#include "../GuiCore.h"
#include "../InternalJson.h"

namespace RobotGui {
    class GuiCore;

    /**
         * @class ServerInterface
         * Server that the GUI receives data from
         *
         * @author Patrick McGuire (Patrick-McGuire)
         */
    class ServerInterface : public QTcpServer, public RobotGui::BaseInterface {
    Q_OBJECT
    public:
        /**
         * Constructor
         * @param _port Port to host on
         */
        explicit ServerInterface(int _port);

        /**
         * Constructor
         */
        ServerInterface();

        /**
         * Deconstruct
         */
        ~ServerInterface();

        /**
         * Sets the widget data structure to impute data to, and initializes things that use it
         * @param _widgetData
         */
        void setWidgetData(WidgetData *_widgetData) override;

        /**
         * Starts the server running
         */
        void startServer();

    public slots:
        /**
         * Handles a incoming connection
         */
        void incomingConnection();

        /**
         * Runs when ever the server is posted to
         */
        void receiveData();

    signals:
        /**
         * Signal to emit when we have new data
         */
        void newData();

    private:
        DataInput *dataInput;
        InternalJson::SharedPtr output = InternalJson::create(InternalJson::map_t);
        int port;
        const int defaultPort = 1254;
    };
}


#endif //ROBOT_GUI_V3_SERVERINTERFACE_H
