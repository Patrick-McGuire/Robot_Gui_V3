//
// Created by nathan on 12/30/21.
//

#ifndef ROBOT_GUI_V3_BASICIMAGEDISPLAY_H
#define ROBOT_GUI_V3_BASICIMAGEDISPLAY_H

#include <QLabel>

#include "../../WidgetData.h"

class BasicImageDisplay : public QLabel {
public:
    BasicImageDisplay(QImage _image, int _targetWidth, int _targetHeight, QWidget *parent = nullptr);

    void setTargetDimensions(int _targetWidth, int _targetHeight);

    void setRotation(double _rotation);

    void drawImage();

protected:
    QImage image;
    QImage resizedImage;

    int targetWidth = 100;
    int targetHeight = 100;
    double rotation = 0;
};


#endif //ROBOT_GUI_V3_BASICIMAGEDISPLAY_H
