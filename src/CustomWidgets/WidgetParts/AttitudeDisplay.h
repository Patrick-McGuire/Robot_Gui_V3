//
// Created by nathan on 5/2/22.
//

#ifndef ROBOT_GUI_V3_ATTITUDEDISPLAY_H
#define ROBOT_GUI_V3_ATTITUDEDISPLAY_H

#include <QLabel>

#include "BasicImageDisplay.h"
#include "../../WidgetData.h"


namespace RobotGui {
    class AttitudeDisplay : public QLabel {
    public:
        AttitudeDisplay(WidgetData *widgetData, QWidget *parent = nullptr);

        void setSize(int size);

        void setRollPitch(double roll, double pitch);

        void refreshMask();

        void paintEvent(QPaintEvent *) override;

    protected:
        BasicImageDisplay *crosshairImageDisplay;
        BasicImageDisplay *rollPointerImageDisplay;
        BasicImageDisplay *rollIndicatorImageDisplay;

    private:
        double roll = 0;
        double pitch = 0;

        double size = 0;
    };
}


#endif //ROBOT_GUI_V3_ATTITUDEDISPLAY_H
