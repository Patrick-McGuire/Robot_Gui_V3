#include <QGridLayout>

#include "MultiBarGraphWidget.h"
#include "../WidgetParts/SimpleBarGraph.h"
#include "../WidgetParts/CircleBarGraph.h"
#include "../../WidgetData.h"
#include "../../InternalJson.h"
#include "../../Theme.h"
#include "../BaseStructure/BaseWidget.h"

#define SIMPLE_BAR_GRAPH_NAME "SimpleBarGraph"
#define CIRCLE_BAR_GRAPH_NAME "CircleBarGraph"

RobotGui::MultiBarGraphWidget::MultiBarGraphWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    configurablePos = true;

    if(configInfo->type == MULTI_BAR_GRAPH) {
        lineConfig = std::dynamic_pointer_cast<LineConfig> (configInfo);
    } else {
        lineConfig = LineConfig::create();
    }

    auto *layout = new QGridLayout();
    for (auto &line : lineConfig->lines) {
        // Make sure everything is initialized
        if(!line.color.is_initialized()) { line.color = ""; }
        if(!line.min.is_initialized()) { line.min = 0; }
        if(!line.max.is_initialized()) { line.max = 100; }
        if(!line.type.is_initialized()) { line.type = "NONE SPECIFIED"; }

        if (line.type.get() == SIMPLE_BAR_GRAPH_NAME) {
            subGraphVector.push_back(new SimpleBarGraph(nullptr, line.label, line.min.get(), line.max.get(), 200, line.color.get()));
            subGraphSourcesVector.push_back(line.source);
            layout->addWidget(subGraphVector[subGraphVector.size() - 1], 1, subGraphVector.size());
        } else if (line.type.get() == CIRCLE_BAR_GRAPH_NAME) {
            subGraphVector.push_back(new CircleBarGraph(nullptr, line.label, line.min.get(), line.max.get(), 200, line.color.get()));
            subGraphSourcesVector.push_back(line.source);
            layout->addWidget(subGraphVector[subGraphVector.size() - 1], 1, subGraphVector.size());
        } else {
            std::cout << "Unable to add graph of type " << line.type.get() << std::endl;
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

void RobotGui::MultiBarGraphWidget::parseXml(const RobotGui::WidgetBaseConfig::SharedPtr &parentConfig, rapidxml::xml_node<> *node) {
    // Iterate though all lines
    for (auto *line = node->first_node(); line; line = line->next_sibling()) {
        std::string tagName = line->name();
        if (tagName == RobotGui::Xml::LINE_TAG) {
            LineConfig::LineInfo configStruct;

            for (rapidxml::xml_attribute<> *attr = line->first_attribute(); attr; attr = attr->next_attribute()) {
                std::string attrName = attr->name();
                std::string attrVal = attr->value();

                if (attrName == RobotGui::Xml::TYPE_ATR) {
                    configStruct.type = attrVal;
                } else if (attrName == RobotGui::Xml::SOURCE_ATR) {
                    configStruct.source = attrVal;
                } else if (attrName == RobotGui::Xml::TITLE_ATR) {
                    configStruct.label = attrVal;
                } else if (attrName == RobotGui::Xml::MINIMUM_ATR) {
                    configStruct.min = std::atof(attrVal.c_str());
                } else if (attrName == RobotGui::Xml::MAXIMUM_ATR) {
                    configStruct.max = std::atof(attrVal.c_str());
                } else if (attrName == RobotGui::Xml::COLOR_ATR) {
                    configStruct.color = attrVal;
                }
            }
            if(parentConfig->type == MULTI_BAR_GRAPH) {
                std::dynamic_pointer_cast<LineConfig>(parentConfig)->lines.push_back(configStruct);
            }
        }
    }
}

void RobotGui::MultiBarGraphWidget::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {
    for(auto & lineConfig : lineConfig->lines) {
        rapidxml::xml_node<> *line = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::LINE_TAG);
        node->append_node(line);
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::TYPE_ATR, lineConfig.type->c_str()));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::SOURCE_ATR, lineConfig.source.c_str()));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::TITLE_ATR, lineConfig.label.c_str()));

        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::MINIMUM_ATR, doc->allocate_string(std::to_string(lineConfig.min.get()).c_str())));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::MAXIMUM_ATR, doc->allocate_string(std::to_string(lineConfig.max.get()).c_str())));

        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::COLOR_ATR, lineConfig.color->c_str()));
    }
}

void RobotGui::MultiBarGraphWidget::customUpdateStyle() {
    for (auto &graph : subGraphVector) {
        graph->setTextColor(bodyTextColor);
    }
}
