//
// Created by nathan on 12/25/21.
//

#ifndef ROBOT_GUI_V3_BASEGRAPHDISPLAY_H
#define ROBOT_GUI_V3_BASEGRAPHDISPLAY_H

#include <QLabel>
#include <utility>
#include "../../CommonFunctions.h"

class BaseGraphDisplay : public QLabel {
public:
    explicit BaseGraphDisplay(QWidget *parent = nullptr) : QLabel(parent) {}

    virtual void setSize(int _size) { size = _size; }

    void setValue(double _data_value) { dataValue = _data_value; }

    void setTextColor(const std::string &_color_string) {
        textColor = CommonFunctions::GetQColorFromString(_color_string);
    }

protected:
    int size = 200;
    double dataValue = 0;
    double minValue = 0;
    double maxValue = 100;
    std::string title;

    QColor barColor;
    QColor textColor;
};

#endif //ROBOT_GUI_V3_BASEGRAPHDISPLAY_H
