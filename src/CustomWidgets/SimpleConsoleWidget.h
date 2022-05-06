//
// Created by nathan on 12/26/21.
//

#ifndef ROBOT_GUI_V3_SIMPLECONSOLEWIDGET_H
#define ROBOT_GUI_V3_SIMPLECONSOLEWIDGET_H

#include "BaseWidgetHelper/BaseWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"

namespace RobotGui {
    class SimpleConsoleWidget : public BaseWidget {
    public:
        SimpleConsoleWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme, bool _borderEnabled=true);

        void updateInFocus() override;

        void paintEvent(QPaintEvent *_event) override;

        void adjustSize();

    protected:
        std::string source;
        std::string title;
        bool drawTitle = false;
        bool borderEnabled;
        int maxLineWidth = 0;
        int numberOfLines = 0;
        int lineSpace = 3;
    };
}


#endif //ROBOT_GUI_V3_SIMPLECONSOLEWIDGET_H
