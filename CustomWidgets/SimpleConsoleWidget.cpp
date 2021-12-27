//
// Created by nathan on 12/26/21.
//

#include <QtGui/QPainter>
#include "SimpleConsoleWidget.h"
#include "../CommonFunctions.h"

SimpleConsoleWidget::SimpleConsoleWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    source = configInfo->source;
    title = configInfo->title;
    drawTitle = !title.empty();
}

void SimpleConsoleWidget::updateInFocus() {
    if (widgetData->keyUpdated(source)) {
        if (widgetData->getKeyType(source) == WidgetData::vector_t) {
            update();
            adjustSize();
        }
    }
}

void SimpleConsoleWidget::paintEvent(QPaintEvent *_event) {
    auto consoleData = widgetData->getJSON(source)->vector;
    int startIndex = consoleData[0]->intVal;
    int fontHeight = fontInfo().pixelSize();
    maxLineWidth = title.length();
    int titleHeight = 0;

    BaseWidget::paintEvent(_event);
    QPainter painter(this);

    if (drawTitle) {
        painter.setPen(CommonFunctions::GetQColorFromString(titleTextColor));
        painter.drawText(5, fontHeight, QString::fromStdString(title));
        titleHeight = fontHeight;
        numberOfLines = int(consoleData.size());
    } else {
        numberOfLines = int(consoleData.size()) - 1;
    }

    for (int i = startIndex; i < startIndex + consoleData.size() - 1; i++) {
        int realIndex = i;
        if (realIndex >= consoleData.size()) { realIndex -= (int(consoleData.size()) - 1); }
        std::string line = consoleData[realIndex]->vector[0]->stringVal;
        int status = consoleData[realIndex]->vector[1]->intVal;
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

void SimpleConsoleWidget::adjustSize() {
    int height = fontInfo().pixelSize() * numberOfLines + 5;
    int width = int(fmax(fontInfo().pixelSize() * 0.7 * maxLineWidth, 1));
    resize(width, height);
}



