//
// Created by nathan on 12/26/21.
//

#ifndef ROBOT_GUI_V3_ANNUNCIATORWIDGET_H
#define ROBOT_GUI_V3_ANNUNCIATORWIDGET_H

#include "BaseWidgetHelper/BaseWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"

#include <QLabel>

namespace RobotGui {
    class AnnunciatorWidget : public RobotGui::BaseWidget {
    public:
        AnnunciatorWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme);

        void updateInFocus() override;

        void customUpdateStyle() override;

    private:
        QLabel *titleWidget;
        std::vector<QLabel *> annunciatorWidgetVector;

        std::string source;
    };
}


#endif //ROBOT_GUI_V3_ANNUNCIATORWIDGET_H
