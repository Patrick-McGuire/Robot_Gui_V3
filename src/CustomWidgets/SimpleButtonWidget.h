#ifndef ROBOT_GUI_V3_SIMPLEBUTTONWIDGET_H
#define ROBOT_GUI_V3_SIMPLEBUTTONWIDGET_H

#include "BaseWidget.h"
#include <QWidget>
#include <string>
#include <QPushButton>
#include "../WidgetData.h"
#include "../RobotGui.h"
#include "../Theme.h"
#include "../WidgetData.h"
#include "../Theme.h"

namespace RobotGui {
    /**
         * @class SimpleButtonWidget
         * Custom QWidget button
         *
         * @author Patrick McGuire (Patrick-McGuire)
         */
    class SimpleButtonWidget : public BaseWidget {
    Q_OBJECT
    public:
        /**
         * Constructor
         * @param parent QWidget to make parent
         * @param configInfo configuration data
         * @param widgetData global widgetData object
         */
        SimpleButtonWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme);

        /**
         * Parses a xml node into the config struct
         * @param parentConfig[out] struct to store data into
         * @param node[in] xml node to parse
         */
        static void parseXml(const WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node);

        /**
         * Saves any configuration data to a xml node
         * @param node node to output to
         */
        void outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) override;

    private slots:

        /**
         * Onclick slot
         */
        void onClick();

        /**
         * On release slot
         */
        void onRelease();

    private:
        /**
         * Updates the style of this widget
         * @param overwrite if we should overwrite any attributes with theme
         */
        void customUpdateStyle() override;

        QPushButton *button;
        bool state = false;
        const char *const BUTTON_WIDGET_NAME = "BUTTON";
    };
}


#endif //ROBOT_GUI_V3_SIMPLEBUTTONWIDGET_H