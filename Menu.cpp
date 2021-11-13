//
// Created by patrick on 11/12/21.
//

#include "Menu.h"

Menu::Menu(QWidget *parent, AppConfig *_config) : QWidget(parent) {
    config = _config;
    auto *menu = new QMenuBar(parent);
    auto *file = new QMenu("Settings");
    file->addAction("&Remove Default XML", this, SLOT(removeDefaultXML()));
    menu->addMenu(file);
    this->setFixedHeight(menu->height());
}

void Menu::removeDefaultXML() {
    config->setDefaultXmlPath(appConfigNoXmlPath);
    config->write();
}
