//
// Created by nathan on 12/25/21.
//

#ifndef ROBOT_GUI_V3_BASEGRAPHDISPLAY_H
#define ROBOT_GUI_V3_BASEGRAPHDISPLAY_H

#include <QLabel>

class BaseGraphDisplay : public QLabel {
public:
    explicit BaseGraphDisplay(QWidget *parent = nullptr) {}

    virtual void setSize(int _size) { size = _size; }

    void setValue(double _data_value) { dataValue = _data_value; }

protected:
    int size;
    double dataValue = 0;
    double minValue;
    double maxValue;
    std::string title;

    QColor barColor;
    QColor textColor;
};

#endif //ROBOT_GUI_V3_BASEGRAPHDISPLAY_H
