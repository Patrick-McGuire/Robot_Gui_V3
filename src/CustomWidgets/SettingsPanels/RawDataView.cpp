//
// Created by nathan on 1/26/22.
//

#include "RawDataView.h"

#include "QGridLayout"
#include "QScrollArea"
#include "../../WidgetData.h"
#include "../../Theme.h"


RobotGui::RawDataView::RawDataView(QWidget *parent, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme) : BaseSettingsPanel(parent, widgetData, theme) {
    lineTextDisplay = new RobotGui::LineTextDisplay();
    scrollArea = new QScrollArea();
    scrollArea->setWidget(lineTextDisplay);
    scrollArea->setStyleSheet("background: transparent");

    setLayout(new QGridLayout());
    layout()->addWidget(scrollArea);
}

void RobotGui::RawDataView::updateInFocus() {
    auto keys = widgetData->getJson()->mapKeys();
    auto data = widgetData->getJson();

    for (int i = 0; i < keys.size() - 1; i++) {
        lineTextDisplay->setLine(i, keys[i], data->mapGet(keys[i])->toString(false));
    }
    lineTextDisplay->clearLinesAfterIndex(int(keys.size()) - 1);

    lineTextDisplay->updateDisplayString(true);
}

void RobotGui::RawDataView::customUpdateStyle() {
    lineTextDisplay->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
}
