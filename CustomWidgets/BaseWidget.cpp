#include "BaseWidget.h"
#include "../WidgetInfo.h"

BaseWidget::BaseWidget(QWidget *parent, WidgetInfo *configInfo) : QWidget(parent) {
    _name = configInfo->name;
    _configInfo = configInfo;
//    setPosition(x, y);
}

void BaseWidget::setPosition(int x, int y) {
    _x = x;
    _y = y;
    move(x, y);
}