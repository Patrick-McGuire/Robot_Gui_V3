//
// Created by nathan on 12/25/21.
//

#include <QGridLayout>

#include "MultiBarGraphWidget.h"
#include "WidgetParts/SimpleBarGraph.h"
#include "WidgetParts/CircleBarGraph.h"
#include "../WidgetData.h"
#include "../InternalJson.h"
#include "../Theme.h"
#include "BaseWidget.h"

#define SIMPLE_BAR_GRAPH_NAME "SimpleBarGraph"
#define CIRCLE_BAR_GRAPH_NAME "CircleBarGraph"

RobotGui::MultiBarGraphWidget::MultiBarGraphWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    configurablePos = true;
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

void RobotGui::MultiBarGraphWidget::updateInFocus() {
    for (int i = 0; i < subGraphVector.size(); i++) {
        auto key = subGraphSourcesVector[i];
        auto subGraph = subGraphVector[i];
        RobotGui::InternalJson::SharedPtr jsonVal = widgetData->getJson()->mapGet(key);
        if (widgetData->keyUpdated(key)) {
            if (jsonVal->getType() == RobotGui::InternalJson::int_t) {
                subGraph->setValue(jsonVal->getInt());
                subGraph->update();
            } else if (jsonVal->getType() == RobotGui::InternalJson::double_t) {
                subGraph->setValue(jsonVal->getDouble());
                subGraph->update();
            }
        }
    }
}

void RobotGui::MultiBarGraphWidget::parseXml(const RobotGui::WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {
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

void RobotGui::MultiBarGraphWidget::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {
    for(auto & lineConfig : configInfo->graphLines) {
        rapidxml::xml_node<> *line = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::LINE_TAG);
        node->append_node(line);
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::TYPE_ATR, lineConfig.type.c_str()));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::SOURCE_ATR, lineConfig.source.c_str()));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::TITLE_ATR, lineConfig.title.c_str()));

        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::MINIMUM_ATR, doc->allocate_string(std::to_string(lineConfig.min).c_str())));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::MAXIMUM_ATR, doc->allocate_string(std::to_string(lineConfig.max).c_str())));

        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::COLOR_ATR, lineConfig.colorString.c_str()));
    }
}

void RobotGui::MultiBarGraphWidget::customUpdateStyle() {
    for (auto &graph : subGraphVector) {
        graph->setTextColor(bodyTextColor);
    }
}
