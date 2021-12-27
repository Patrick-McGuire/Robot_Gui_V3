//
// Created by nathan on 12/26/21.
//

#ifndef ROBOT_GUI_V3_ANNUNCIATORWIDGET_H
#define ROBOT_GUI_V3_ANNUNCIATORWIDGET_H

#include "BaseWidget.h"

#include <QLabel>

class AnnunciatorWidget: public BaseWidget {
public:
    AnnunciatorWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme);

    void updateInFocus() override;

private:
    QLabel *titleWidget;
    std::vector<QLabel*> annunciatorWidgetVector;

    std::string source;
};


#endif //ROBOT_GUI_V3_ANNUNCIATORWIDGET_H
