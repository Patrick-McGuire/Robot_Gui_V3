//
// Created by nathan on 12/25/21.
//

#include <QGridLayout>

#include "MultiBarGraphWidget.h"
#include "WidgetParts/SimpleBarGraph.h"
#include "WidgetParts/CircleBarGraph.h"

#define SIMPLE_BAR_GRAPH_NAME "SimpleBarGraph"
#define CIRCLE_BAR_GRAPH_NAME "CircleBarGraph"

MultiBarGraphWidget::MultiBarGraphWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    auto *layout = new QGridLayout();

    for (auto &line : configInfo->graphLines) {
        if (line.type == SIMPLE_BAR_GRAPH_NAME) {
            subGraphVector.push_back(new SimpleBarGraph(nullptr, line.title, line.min, line.max, 200, line.colorString));
            subGraphSourcesVector.push_back(line.source);
            layout->addWidget(subGraphVector[subGraphVector.size() - 1], 1, subGraphVector.size());
        } else if (line.type == CIRCLE_BAR_GRAPH_NAME) {
            subGraphVector.push_back(new CircleBarGraph(nullptr, line.title, line.min, line.max, 200, line.colorString));
            subGraphSourcesVector.push_back(line.source);
            layout->addWidget(subGraphVector[subGraphVector.size() - 1], 1, subGraphVector.size());
        } else {
            std::cout << "Unable to add graph of type " << line.type << std::endl;
        }
    }

    setLayout(layout);
    adjustSize();
    update();
}

void MultiBarGraphWidget::updateInFocus() {
    for (int i = 0; i < subGraphVector.size(); i++) {
        auto key = subGraphSourcesVector[i];
        auto subGraph = subGraphVector[i];

        if (widgetData->keyUpdated(key)) {
            if (widgetData->getKeyType(key) == WidgetData::int_t) {
                subGraph->setValue(widgetData->getInt(key));
                subGraph->update();
            } else if (widgetData->getKeyType(key) == WidgetData::double_t) {
                subGraph->setValue(widgetData->getDouble(key));
                subGraph->update();
            }
        }
    }
}

void MultiBarGraphWidget::parseXml(const RobotGui::WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {
    // Iterate though all lines
    for (auto *line = node->first_node(); line; line = line->next_sibling()) {
        std::string tagName = line->name();
        if (tagName == RobotGui::Xml::LINE_TAG) {
            RobotGui::GraphLineConfig configStruct;

            for (rapidxml::xml_attribute<> *attr = line->first_attribute(); attr; attr = attr->next_attribute()) {
                std::string attrName = attr->name();
                std::string attrVal = attr->value();

                if (attrName == RobotGui::Xml::TYPE_ATR) {
                    configStruct.type = attrVal;
                } else if (attrName == RobotGui::Xml::SOURCE_ATR) {
                    configStruct.source = attrVal;
                } else if (attrName == RobotGui::Xml::TITLE_ATR) {
                    configStruct.title = attrVal;
                } else if (attrName == RobotGui::Xml::MINIMUM_ATR) {
                    configStruct.min = std::atof(attrVal.c_str());
                } else if (attrName == RobotGui::Xml::MAXIMUM_ATR) {
                    configStruct.max = std::atof(attrVal.c_str());
                } else if (attrName == RobotGui::Xml::COLOR_ATR) {
                    configStruct.colorString = attrVal;
                }
            }

            parentConfig->graphLines.push_back(configStruct);
        }
    }
}
