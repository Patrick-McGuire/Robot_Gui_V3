//
// Created by nathan on 12/25/21.
//

#ifndef ROBOT_GUI_V3_CIRCLEBARGRAPH_H
#define ROBOT_GUI_V3_CIRCLEBARGRAPH_H

#include "BaseGraphDisplay.h"

namespace RobotGui {
    class CircleBarGraph : public BaseGraphDisplay {
    public:
        explicit CircleBarGraph(QWidget *parent = nullptr, std::string _title = "Title", double min_value = 0, double _max_value = 100, int _size = 200, const std::string &bar_color = "");

        void setSize(int size);

        void paintEvent(QPaintEvent *_event) override;
    };
}


#endif //ROBOT_GUI_V3_CIRCLEBARGRAPH_H
