//
// Created by patrick on 11/6/21.
//

#ifndef ROBOT_GUI_V3_TABWIDGET_H
#define ROBOT_GUI_V3_TABWIDGET_H

#include "BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include "../ConfigStructs.h"
#include <string>
#include "../WidgetData.h"
#include "../Constants.h"
#include "../XML/XMLConstants.h"
#include "../XML/XMLInput.h"
#include <QTabWidget>
#include <QString>
#include "../GUIMaker.h"

class TabWidget : public BaseWidget  {
private:
    QGridLayout layout;
    QTabWidget *tabs;
    std::vector<QWidget*> pages;
    std::vector<BaseWidget*> widgets;

    static void parseTabChildren(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);

public:
    TabWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData);

    static void parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);

    void updateInFocus() override;
    void updateNoFocus() override;
    void updateOnInFocus() override;
};


#endif //ROBOT_GUI_V3_TABWIDGET_H
