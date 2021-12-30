//
// Created by nathan on 12/30/21.
//

#ifndef ROBOT_GUI_V3_BASICIMAGEDISPLAY_H
#define ROBOT_GUI_V3_BASICIMAGEDISPLAY_H

#include <QLabel>

#include "../../WidgetData.h"

class BasicImageDisplay : public QLabel {
public:
    BasicImageDisplay(QImage _image, int _targetWidth, QWidget *parent = nullptr);

    void setTargetWidth(int _targetWidth);

protected:
    QImage image;
    int targetWidth;
};


#endif //ROBOT_GUI_V3_BASICIMAGEDISPLAY_H
