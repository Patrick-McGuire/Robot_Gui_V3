//
// Created by nathan on 12/26/21.
//

#ifndef ROBOT_GUI_V3_ANNUNCIATORWIDGET_H
#define ROBOT_GUI_V3_ANNUNCIATORWIDGET_H

#include "BaseWidget.h"

#include <QLabel>

class AnnunciatorWidget: public BaseWidget {
public:
    AnnunciatorWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData);

private:
    QLabel *titleWidget;
    std::vector<QLabel*> annunciatorWidgetVector;
};


#endif //ROBOT_GUI_V3_ANNUNCIATORWIDGET_H
