//
// Created by nathan on 12/25/21.
//

#include <QGridLayout>

#include "MultiBarGraphWidget.h"
#include "../XML/XMLConstants.h"

#define SIMPLE_BAR_GRAPH_NAME "SimpleBarGraph"

MultiBarGraphWidget::MultiBarGraphWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    auto *layout = new QGridLayout();

    for (auto &line : configInfo->graphLines) {
        if (line.type == SIMPLE_BAR_GRAPH_NAME) {
            subGraphVector.push_back(new SimpleBarGraph(nullptr, line.title, line.min, line.max, 200, line.colorString));
            subGraphSourcesVector.emplace_back(line.source);
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
}

void MultiBarGraphWidget::parseXml(const WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {
    // Iterate though all lines
    for (auto *line = node->first_node(); line; line = line->next_sibling()) {
        std::string tagName = line->name();
        if (tagName == XML_LINE_TAG) {
            GraphLineConfig configStruct;

            for (rapidxml::xml_attribute<> *attr = line->first_attribute(); attr; attr = attr->next_attribute()) {
                std::string attrName = attr->name();
                std::string attrVal = attr->value();

                if (attrName == XML_TYPE_ATR) {
                    configStruct.type = attrVal;
                } else if (attrName == XML_SOURCE_ATR) {
                    configStruct.source = attrVal;
                } else if (attrName == XML_TITLE_ATR) {
                    configStruct.title = attrVal;
                } else if (attrName == XML_MINIMUM_ATR) {
                    configStruct.min = std::atof(attrVal.c_str());
                } else if (attrName == XML_MAXIMUM_ATR) {
                    configStruct.max = std::atof(attrVal.c_str());
                } else if (attrName == XML_COLOR_ATR) {
                    configStruct.colorString = attrVal;
                }
            }

            parentConfig->graphLines.push_back(configStruct);
        }
    }
}
