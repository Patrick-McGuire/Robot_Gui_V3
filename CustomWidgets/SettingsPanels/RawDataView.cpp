//
// Created by nathan on 1/26/22.
//

#include "RawDataView.h"

#include "QGridLayout"


RawDataView::RawDataView(QWidget *parent, WidgetData *widgetData, Theme *theme) : BaseSettingsPanel(parent, widgetData, theme) {
    lineTextDisplay = new LineTextDisplay();

    setLayout(new QGridLayout());
    layout()->addWidget(lineTextDisplay);
}

void RawDataView::updateInFocus() {
    auto keys = widgetData->getJson()->mapKeys();
    auto data = widgetData->getJson();

    for (int i = 0; i < keys.size() - 1; i++) {
        lineTextDisplay->setLine(i, keys[i], data->mapGet(keys[i])->toString());
    }
    lineTextDisplay->clearLinesAfterIndex(keys.size() - 1);

    lineTextDisplay->updateDisplayString(false);
}

void RawDataView::customUpdateStyle() {
    lineTextDisplay->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
}
