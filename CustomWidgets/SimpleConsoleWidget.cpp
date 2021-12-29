//
// Created by nathan on 12/26/21.
//

#include <QtGui/QPainter>
#include "SimpleConsoleWidget.h"
#include "../CommonFunctions.h"

SimpleConsoleWidget::SimpleConsoleWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme, bool _borderEnabled) : BaseWidget(parent, configInfo, widgetData, theme) {
    source = configInfo->source;
    title = configInfo->title;
    drawTitle = !title.empty();
    borderEnabled = _borderEnabled;

    setFont(QFont("Monospace", font().pointSize()));
}

void SimpleConsoleWidget::updateInFocus() {
    if (widgetData->keyUpdated(source)) {
        if (widgetData->getKeyType(source) == WidgetData::json_t && widgetData->getJSON(source)->getType() == InternalJson::vector_t) {
            update();
            adjustSize();
        }
    }
}

void SimpleConsoleWidget::paintEvent(QPaintEvent *_event) {
    if (borderEnabled) { BaseWidget::paintEvent(_event); }
    if (widgetData->getKeyType(source) != WidgetData::json_t) { return; }
    if (widgetData->getJSON(source)->getType() != InternalJson::vector_t) { return; }
    
    InternalJson::SharedPtr consoleData = widgetData->getJSON(source);
    int startIndex = consoleData->vectorGet(0)->getInt();

    int fontHeight = fontInfo().pixelSize() + lineSpace;
    maxLineWidth = title.length();
    int titleHeight = 0;

    QPainter painter(this);
    if (drawTitle) {
        painter.setPen(CommonFunctions::GetQColorFromString(titleTextColor));
        painter.drawText(5, fontHeight, QString::fromStdString(title));
        titleHeight = fontHeight;
        numberOfLines = int(consoleData->vectorSize());
    } else {
        numberOfLines = int(consoleData->vectorSize()) - 1;
    }

    for (int i = startIndex; i < startIndex + consoleData->vectorSize() - 1; i++) {
        int realIndex = i;
        if (realIndex >= consoleData->vectorSize()) { realIndex -= (int(consoleData->vectorSize()) - 1); }
        if(consoleData->vectorGet(realIndex)->getType() == InternalJson::vector_t) {
            std::string line = consoleData->vectorGet(realIndex)->vectorGet(0)->getString();
            int status = consoleData->vectorGet(realIndex)->vectorGet(1)->getInt();
            maxLineWidth = fmax(maxLineWidth, line.length());

            if (status == 0) {
                painter.setPen(CommonFunctions::GetQColorFromString(bodyTextColor));
            } else if (status == 1) {
                painter.setPen(QColor("yellow"));
            } else if (status == 2) {
                painter.setPen(QColor("red"));
            } else {
                painter.setPen(QColor("blue"));
            }

            painter.drawText(5, fontHeight * (realIndex) + titleHeight, QString::fromStdString(line));
        }
    }
}

void SimpleConsoleWidget::adjustSize() {
    int height = (fontInfo().pixelSize() + lineSpace) * numberOfLines + 5 - lineSpace;
    int width = int(fmax(fontInfo().pixelSize() * 0.7 * maxLineWidth, 1));
    resize(width, height);
    setMinimumHeight(height);
    setMinimumWidth(width);
}



