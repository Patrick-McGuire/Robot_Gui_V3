#ifndef ROBOT_GUI_V3_TEXTBOXWIDGET_H
#define ROBOT_GUI_V3_TEXTBOXWIDGET_H

#include "BaseWidget.h"

#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include <string>

#include "WidgetParts/LineTextDisplay.h"
#include "../WidgetData.h"
#include "../RobotGui.h"
#include "../Theme.h"
#include "../WidgetData.h"

namespace RobotGui {
    /**
         * @class TextBoxWidget
         * Custom QWidget that displays text-value pairs
         *
         * @author Patrick McGuire (Patrick-McGuire)
         */
    class TextBoxWidget : public BaseWidget {
    Q_OBJECT
    public:
        /**
         * Constructor
         * @param parent QWidget to make parent
         * @param configInfo configuration data
         * @param widgetData global widgetData object
         * @param _theme theme object
         */
        TextBoxWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme);

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

    private:
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

        /**
         * Updates the style of this widget
         * @param overwrite if we should overwrite any attributes with theme
         */
        void customUpdateStyle() override;

        LineTextDisplay *textBox;
        QLabel *titleBox;
        QGridLayout *layout;
        std::vector<std::string> lineKeys;
        const char *const textBoxTittleBoxName = "TITTLE_BOX";
        const char *const textBoxTextBoxName = "TEXT_BOX";
    };
}

#endif //ROBOT_GUI_V3_TEXTBOXWIDGET_H
