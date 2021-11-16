//
// Created by patrick on 11/15/21.
//

#include "MenuWidget.h"

MenuWidget::MenuWidget(QWidget *parent, AppConfig *appConfig_, CoreGUI *coreGui) : QMenuBar(parent) {
    appConfig = appConfig_;
    auto *file = new QMenu("Settings");
    file->addAction("Remove Default XML", this, SLOT(removeDefaultXML()));
    file->addAction("Restart", coreGui, SLOT(restartGUI()));
    this->addMenu(file);
}

void MenuWidget::removeDefaultXML() {
    appConfig->setDefaultXmlPath(appConfigNoXmlPath);
    appConfig->write();
}
