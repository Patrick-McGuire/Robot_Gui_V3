#include "BaseWidget.h"

BaseWidget::BaseWidget(QWidget *parent, std::string name, int x, int y) : QWidget(parent) {
    _name = name;
//    setPosition(x, y);
}

void BaseWidget::setPosition(int x, int y) {
    _x = x;
    _y = y;
    move(x, y);
}