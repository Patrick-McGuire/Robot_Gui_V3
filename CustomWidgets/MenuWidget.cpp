//
// Created by patrick on 11/15/21.
//

#include "MenuWidget.h"

MenuWidget::MenuWidget(QWidget *parent, AppConfig *appConfig_, CoreGUI *coreGui, RobotGUI *robotGui) : QMenuBar(parent) {
    appConfig = appConfig_;
    // File menu
    auto *file = new QMenu("File");
    file->addAction("Open", coreGui, SLOT(openReload()));
    file->addAction("Reload", coreGui, SLOT(reload()));
    file->addAction("Reparse", coreGui, SLOT(reparseReload()));
    // Settings menu
    auto *settings = new QMenu("Settings");
    settings->addAction("Make all draggable", robotGui, SLOT(makeWidgetsDraggable()));
    settings->addAction("Make all fixed", robotGui, SLOT(makeWidgetsFixed()));
    // Theme menu
    auto *theme = new QMenu("Theme");
    auto *setTheme = theme->addMenu("Set theme");

    auto *subMenuAct1 = setTheme->addAction("1");
    subMenuAct1->setData(QString("1"));
    auto *subMenuAct2 = setTheme->addAction("2");
    subMenuAct2->setData(QString("2"));
    auto *subMenuAct3 = setTheme->addAction("3");
    subMenuAct3->setData(QString("3"));

    connect(setTheme, SIGNAL(triggered(QAction*)), this, SLOT(removeDefaultXML(QAction*)));

    theme->addMenu(setTheme);
    auto *setAll = theme->addMenu("Set theme for all");
    setAll->addAction("1");
    setAll->addAction("2");
    setAll->addAction("3");
    theme->addMenu(setAll);
    // Finishing up
    this->addMenu(file);
    this->addMenu(settings);
    this->addMenu(theme);
}

void MenuWidget::removeDefaultXML(QAction *channelAction) {
    std::cout << channelAction->data().toString().toStdString() << "\n";
//    appConfig->setDefaultXmlPath(appConfigNoXmlPath);
//    appConfig->write();
}
