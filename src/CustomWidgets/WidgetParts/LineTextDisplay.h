//
// Created by nathan on 12/29/21.
//

#ifndef ROBOT_GUI_V3_LINETEXTDISPLAY_H
#define ROBOT_GUI_V3_LINETEXTDISPLAY_H

#include <QLabel>

class LineTextDisplay : public QLabel {
public:
    explicit LineTextDisplay(QWidget *parent = nullptr);

    void setLine(int index, std::string name, std::string value);

    void clearLinesAfterIndex(int index);

    void updateDisplayString(bool auto_scale=true);

protected:
    std::vector<std::array<std::string, 2>> lines;
};


#endif //ROBOT_GUI_V3_LINETEXTDISPLAY_H
