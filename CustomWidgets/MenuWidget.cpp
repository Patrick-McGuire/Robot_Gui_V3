//
// Created by patrick on 11/15/21.
//

#include "MenuWidget.h"

MenuWidget::MenuWidget(QWidget *parent, AppConfig *appConfig_, CoreGUI *coreGui, RobotGUI *robotGui) : QMenuBar(parent) {
    appConfig = appConfig_;
    auto *file = new QMenu("File");
    file->addAction("Open", coreGui, SLOT(openReload()));
    file->addAction("Reload", coreGui, SLOT(reload()));
    file->addAction("Reparse", coreGui, SLOT(reparseReload()));
    auto *settings = new QMenu("Settings");
    settings->addAction("Make all draggable", robotGui, SLOT(makeWidgetsDraggable()));
    settings->addAction("Make all fixed", robotGui, SLOT(makeWidgetsFixed()));
    this->addMenu(file);
    this->addMenu(settings);
}

void MenuWidget::removeDefaultXML() {
    appConfig->setDefaultXmlPath(appConfigNoXmlPath);
    appConfig->write();
}
