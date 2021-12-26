//
// Created by nathan on 12/26/21.
//

#ifndef ROBOT_GUI_V3_BROWSE_H
#define ROBOT_GUI_V3_BROWSE_H

#include "BaseWidget.h"

class Browse : public BaseWidget {
public:
    Browse(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData);
};

#endif //ROBOT_GUI_V3_BROWSE_H
