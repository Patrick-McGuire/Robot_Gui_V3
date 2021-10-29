#include <iostream>
#include "BaseWidget.h"
#include "../Configuration/WidgetInfo.h"
#include <QTabWidget>

BaseWidget::BaseWidget(QWidget *parent, WidgetInfo *configInfo, WidgetData *widgetData) : QWidget(parent) {
    _name = &configInfo->name;
    _configInfo = configInfo;
    _widgetData = widgetData;
    _parent = parent;
    draggable = true;
    setPosition(_configInfo->x, _configInfo->y);
}

void BaseWidget::setPosition(int x, int y) {
    // Clip values to be inside the window
    if(x < 0) { x = 0; }
    if(y < 0) { y = 0; }
    if(x > _parent->size().width() - this->width()) { x = _parent->size().width() - this->width(); }
    if(y > _parent->size().height() - this->height()) { y = _parent->size().height() - this->height(); }
    _x = x;
    _y = y;
    move(x, y);
}

void BaseWidget::mousePressEvent(QMouseEvent *event) {
    if(draggable && !_configInfo->staticPos) {
        clicked = true;
        startX = event->globalX();
        startY = event->globalY();
        startWX = _x;
        startWY = _y;
    }
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event) {
    clicked = false;
    startX = event->globalX();
    startY = event->globalY();
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event) {
    if(clicked && draggable && !_configInfo->staticPos) {
        setPosition(event->globalX() - startX + startWX, event->globalY() - startY + startWY );
    }
}

void BaseWidget::updateData() {

}

void BaseWidget::updateInFocus() {

}

void BaseWidget::updateNoFocus() {

}

void BaseWidget::updateOnInFocus() {

}
