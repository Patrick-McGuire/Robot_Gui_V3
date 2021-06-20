#include <iostream>
#include "BaseWidget.h"
#include "../Configuration/WidgetInfo.h"

BaseWidget::BaseWidget(QWidget *parent, WidgetInfo *configInfo, WidgetData *widgetData) : QWidget(parent) {
    _name = configInfo->name;
    _configInfo = configInfo;
    _widgetData = widgetData;
    setPosition(_configInfo->x, _configInfo->y);
//    this->mouseMoveEvent()
//    connect(this, &QWidget::mouseMoveEvent, this, SLOT(mouseMove()));
}

void BaseWidget::setPosition(int x, int y) {
    _x = x;
    _y = y;
    move(x, y);
}

void BaseWidget::updateData() {
    //overwrite
}

void BaseWidget::mousePressEvent(QMouseEvent *event) {
    clicked = true;
    startX = event->globalX();
    startY = event->globalY();
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event) {
    clicked = false;
    startX = event->globalX();
    startY = event->globalY();
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event) {
    if(clicked) {
        setPosition(event->globalX() - startX + this->_x, event->globalY() - startY + this->_y);
        startX = event->globalX();
        startY = event->globalY();
    }
}
