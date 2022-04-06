//
// Created by nathan on 12/30/21.
//

#ifndef ROBOT_GUI_V3_COMPASSDISPLAY_H
#define ROBOT_GUI_V3_COMPASSDISPLAY_H

#include <QLabel>

#include "BasicImageDisplay.h"
#include "../../WidgetData.h"

namespace RobotGui {
    class CompassDisplay : public QLabel {
    public:
        explicit CompassDisplay(WidgetData *widgetData, QWidget *parent = nullptr);

        void setSize(int size);

        void setYaw(double yaw);

    protected:
        BasicImageDisplay *backgroundImageWidget;
        BasicImageDisplay *arrowImageWidget;
    };
}

#endif //ROBOT_GUI_V3_COMPASSDISPLAY_H
