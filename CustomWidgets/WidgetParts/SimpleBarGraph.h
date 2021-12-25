//
// Created by nathan on 12/25/21.
//

#ifndef ROBOT_GUI_V3_SIMPLEBARGRAPH_H
#define ROBOT_GUI_V3_SIMPLEBARGRAPH_H

#include <QWidget>
#include "BaseGraphDisplay.h"

class SimpleBarGraph : public BaseGraphDisplay {
public:
    explicit SimpleBarGraph(QWidget *parent = nullptr, std::string _title = "Title", double min_value = 0, double _max_value = 100, int _size = 200, const std::string &bar_color = "");

    void setSize(int _size) override;

    void paintEvent(QPaintEvent *_event) override;

protected:
    double dataValue = 0;
    double minValue;
    double maxValue;
    std::string title;

    QColor barColor;
    QColor textColor;
};


#endif //ROBOT_GUI_V3_SIMPLEBARGRAPH_H
