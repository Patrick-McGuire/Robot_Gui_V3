#include <iostream>
#include "BaseWidget.h"
#include <QTabWidget>

BaseWidget::BaseWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData) : QWidget(parent) {
    _configInfo = configInfo;
    _widgetData = widgetData;
    _parent = parent;
    draggable = configInfo->draggable;
    inFocusLast = true;
    move(_configInfo->x, _configInfo->y);     // Using move because setPosition clips the values based on parents size, but parents size is not hectically set yet in constructor
}

void BaseWidget::setPosition(int _x, int _y) {
    // Clip values to be inside the window
    if(_x < 0) { _x = 0; }
    if(_y < 0) { _y = 0; }
    if(_x > _parent->size().width() - this->width()) { _x = _parent->size().width() - this->width(); }
    if(_y > _parent->size().height() - this->height()) { _y = _parent->size().height() - this->height(); }
    _configInfo->x = _x;
    _configInfo->y = _y;
    move(_x, _y);
}

void BaseWidget::mousePressEvent(QMouseEvent *event) {
    if(draggable) {
        clicked = true;
        startX = event->globalX();
        startY = event->globalY();
        startWX = _configInfo->x;
        startWY = _configInfo->y;
    }
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event) {
    clicked = false;
    startX = event->globalX();
    startY = event->globalY();
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event) {
    if(clicked && draggable) {
        setPosition(event->globalX() - startX + startWX, event->globalY() - startY + startWY );
    }
}

void BaseWidget::updateData(bool focus) {
    updateData(focus ? _parent : nullptr);
}

void BaseWidget::updateData(QWidget *activeParent) {
    if(activeParent == _parent) {
        if(!inFocusLast) {
            inFocusLast = true;
            updateOnInFocus();
        }
        updateInFocus();
    } else {
        inFocusLast = false;
        updateNoFocus();
    }
}

void BaseWidget::updateInFocus() {

}

void BaseWidget::updateNoFocus() {

}

void BaseWidget::updateOnInFocus() {

}

void BaseWidget::customUpdate() {

}


