//
// Created by nathan on 12/30/21.
//

#ifndef ROBOT_GUI_V3_BASICIMAGEDISPLAY_H
#define ROBOT_GUI_V3_BASICIMAGEDISPLAY_H

#include <QLabel>

#include "../../WidgetData.h"

namespace RobotGui {
    class BasicImageDisplay : public QLabel {
    public:
        BasicImageDisplay(QImage _image, int _targetWidth, int _targetHeight, QWidget *parent = nullptr);

        void setTargetDimensions(int _targetWidth, int _targetHeight, int x_offset = 0, int y_offset = 0, bool x_centered = true, bool y_centered = true);

        void setRotation(double _rotation);

        void drawImage();

    protected:
        QImage image;
        QImage resizedImage;
        QImage rotatedImage;

        int targetWidth = 100;
        int targetHeight = 100;
        int xOffset = 0;
        int yOffset = 0;
        bool xCentered = true;
        bool yCentered = true;

        double rotation = 0;
    };
}


#endif //ROBOT_GUI_V3_BASICIMAGEDISPLAY_H
