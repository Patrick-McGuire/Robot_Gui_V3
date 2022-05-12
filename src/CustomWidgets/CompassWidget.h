//
// Created by nathan on 12/30/21.
//

#ifndef ROBOT_GUI_V3_COMPASSWIDGET_H
#define ROBOT_GUI_V3_COMPASSWIDGET_H

#include "BaseStructure/BaseWidget.h"

#include "WidgetParts/CompassDisplay.h"
#include "../WidgetData.h"
#include "../Theme.h"

namespace RobotGui {
    class CompassWidget : public BaseWidget {
    public:
        CompassWidget(QWidget *parent, const WidgetBaseConfig::SharedPtr &configInfo, WidgetData *widgetData, Theme *theme);

        void updateInFocus() override;

    protected:
        CompassDisplay *compassDisplay;
    };
}


#endif //ROBOT_GUI_V3_COMPASSWIDGET_H
