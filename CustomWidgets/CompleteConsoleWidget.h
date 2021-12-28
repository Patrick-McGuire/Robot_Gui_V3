//
// Created by nathan on 12/28/21.
//

#ifndef ROBOT_GUI_V3_COMPLETECONSOLEWIDGET_H
#define ROBOT_GUI_V3_COMPLETECONSOLEWIDGET_H

#include "BaseWidget.h"
#include <QLabel>
#include <QLineEdit>
#include "SimpleConsoleWidget.h"

class CompleteConsoleWidget : public BaseWidget {
public:
    CompleteConsoleWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme);

    void updateInFocus() override;

    void customUpdateStyle() override ;


protected:
    QLabel *titleWidget;
    QLineEdit *textEntryWidget;
    SimpleConsoleWidget *simpleConsoleWidget;
};


#endif //ROBOT_GUI_V3_COMPLETECONSOLEWIDGET_H
