//
// Created by patrick on 11/15/21.
//

#include "MenuWidget.h"

MenuWidget::MenuWidget(QWidget *parent, WidgetConfig *configInfo, WidgetData *widgetData, AppConfig *appConfig_) : BaseWidget(parent, configInfo, widgetData) {
    appConfig = appConfig_;
    auto *menu = new QMenuBar(parent);
    auto *file = new QMenu("Settings");
    file->addAction("&Remove Default XML", this, SLOT(removeDefaultXML()));
    menu->addMenu(file);
    this->setFixedHeight(menu->height());
}

void MenuWidget::removeDefaultXML() {
    appConfig->setDefaultXmlPath(appConfigNoXmlPath);
    appConfig->write();
}
