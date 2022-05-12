//
// Created by nathan on 5/2/22.
//

#ifndef ROBOT_GUI_V3_ATTITUDEWIDGET_H
#define ROBOT_GUI_V3_ATTITUDEWIDGET_H

#include "../BaseStructure/BaseWidget.h"
#include "SourceMapConfig.h"
#include "../WidgetParts/AttitudeDisplay.h"


namespace RobotGui {
    class AttitudeWidget : public BaseWidget {
    public:
        AttitudeWidget(QWidget *parent, const WidgetBaseConfig::SharedPtr &configInfo, WidgetData *widgetData, Theme *theme);

        void updateInFocus() override;

    protected:
        AttitudeDisplay *attitudeDisplay;

        SourceMapConfig::SharedPtr sourceMapConfig;

    private:
        std::string pitchSource;
        std::string rollSource;

    };
}


#endif //ROBOT_GUI_V3_ATTITUDEWIDGET_H
