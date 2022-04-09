#ifndef ROBOT_GUI_V3_VIDEOWIDGET_H
#define ROBOT_GUI_V3_VIDEOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include <string>
#include "../WidgetData.h"
#include "BaseWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"
#include <QImage>


namespace RobotGui {
    class VideoWidget : public BaseWidget {
    Q_OBJECT
    public:
        /**
         * Constructor
         * @param name  name of widget
         * @param x     x position of the widget
         * @param y     y position of the widget
         */
        VideoWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData, Theme *_theme);

        /**
         * Parses a xml node into the config struct
         * @param parentConfig[out] struct to store data into
         * @param node[in] xml node to parse
         */
        static void parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);

        /**
         * Saves any configuration data to a xml node
         * @param node node to output to
         */
        void outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) override;

        /**
         * Update the widget when in focus
         */
        void updateInFocus() override;

        /**
         * Update the widget when not in focus
         */
        void updateNoFocus() override;

        /**
         * Update the widget when coming into focus
         */
        void updateOnInFocus() override;

        /**
         * Helper function for updating data
         */
        void customUpdate() override;

    private:
        QLabel videoWidget;
        QGridLayout layout;
        bool autoWidth = false;
        bool autoHeight = false;
    };
}

#endif //ROBOT_GUI_V3_VIDEOWIDGET_H
