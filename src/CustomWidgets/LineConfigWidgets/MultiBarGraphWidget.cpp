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

RobotGui::MultiBarGraphWidget::MultiBarGraphWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : BaseWidget(
        parent, configInfo, widgetData, _theme) {
    configInfo->require(WidgetConstants::BACKGROUND_COLOR);
    configInfo->require(WidgetConstants::TEXT_COLOR);


    lineConfig = std::dynamic_pointer_cast<LineConfig>(configInfo);


    auto *layout = new QGridLayout();
    for (auto &line: lineConfig->lines) {
        // Make sure everything is initialized
        if (!line.color.is_initialized()) { line.color = ""; }
        if (!line.min.is_initialized()) { line.min = 0; }
        if (!line.max.is_initialized()) { line.max = 100; }
        if (!line.type.is_initialized()) { line.type = "NONE SPECIFIED"; }

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

void RobotGui::MultiBarGraphWidget::customUpdateStyle() {
    for (auto &graph: subGraphVector) {
        graph->setTextColor(getTextColor());
    }
}
