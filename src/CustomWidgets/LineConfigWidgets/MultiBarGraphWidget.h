#ifndef ROBOT_GUI_V3_MULTIBARGRAPHWIDGET_H
#define ROBOT_GUI_V3_MULTIBARGRAPHWIDGET_H

#include "../BaseStructure/BaseWidget.h"
#include "../WidgetParts/SimpleBarGraph.h"
#include "../../WidgetData.h"
#include "../../Theme.h"
#include "LineConfig.h"

namespace RobotGui {
    class MultiBarGraphWidget : public BaseWidget {
    public:
        MultiBarGraphWidget(QWidget *parent, const WidgetBaseConfig::SharedPtr &configInfo, WidgetData *widgetData, Theme *_theme);

        void updateInFocus() override;

        static void parseXml(const WidgetBaseConfig::SharedPtr &parentConfig, rapidxml::xml_node<> *node);

        /**
         * Saves any configuration data to a xml node
         * @param node node to output to
         */
        void outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) override;

        void customUpdateStyle() override;

    protected:
        int size = 200;

        std::vector<BaseGraphDisplay *> subGraphVector;
        std::vector<std::string> subGraphSourcesVector;

        LineConfig::SharedPtr lineConfig;
    };
}


#endif //ROBOT_GUI_V3_MULTIBARGRAPHWIDGET_H