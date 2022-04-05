//
// Created by nathan on 1/26/22.
//

#include "RawDataView.h"

#include "QGridLayout"
#include "QScrollArea"
#include "../../WidgetData.h"


RawDataView::RawDataView(QWidget *parent, RobotGui::WidgetData *widgetData, Theme *theme) : BaseSettingsPanel(parent, widgetData, theme) {
    lineTextDisplay = new LineTextDisplay();
    scrollArea = new QScrollArea();
    scrollArea->setWidget(lineTextDisplay);
    scrollArea->setStyleSheet("background: transparent");

    setLayout(new QGridLayout());
    layout()->addWidget(scrollArea);
}

void RawDataView::updateInFocus() {
    auto keys = widgetData->getJson()->mapKeys();
    auto data = widgetData->getJson();

    for (int i = 0; i < keys.size() - 1; i++) {
        lineTextDisplay->setLine(i, keys[i], data->mapGet(keys[i])->toString(false));
    }
    lineTextDisplay->clearLinesAfterIndex(int(keys.size()) - 1);

    lineTextDisplay->updateDisplayString(true);
}

void RawDataView::customUpdateStyle() {
    lineTextDisplay->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
}
