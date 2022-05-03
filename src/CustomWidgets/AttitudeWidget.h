//
// Created by nathan on 5/2/22.
//

#ifndef ROBOT_GUI_V3_ATTITUDEWIDGET_H
#define ROBOT_GUI_V3_ATTITUDEWIDGET_H

#include "BaseWidget.h"

#include "WidgetParts/AttitudeDisplay.h"


namespace RobotGui {
    class AttitudeWidget : public BaseWidget {
    public:
        AttitudeWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme);

        void updateInFocus() override;

    protected:
        AttitudeDisplay *attitudeDisplay;

    private:
        std::string pitchSource;
        std::string rollSource;
    };
}


#endif //ROBOT_GUI_V3_ATTITUDEWIDGET_H
