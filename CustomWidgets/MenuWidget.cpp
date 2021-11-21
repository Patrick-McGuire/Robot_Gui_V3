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

    auto *subMenuAct1 = setTheme->addAction(QString::fromStdString(Theme::getThemeName(Themes::Dark)));
    subMenuAct1->setData(QString::fromStdString(Theme::getThemeName(Themes::Dark)));
    auto *subMenuAct2 = setTheme->addAction(QString::fromStdString(Theme::getThemeName(Themes::Light)));
    subMenuAct2->setData(QString::fromStdString(Theme::getThemeName(Themes::Light)));
    auto *subMenuAct3 = setTheme->addAction(QString::fromStdString(Theme::getThemeName(Themes::Green)));
    subMenuAct3->setData(QString::fromStdString(Theme::getThemeName(Themes::Green)));

    connect(setTheme, SIGNAL(triggered(QAction*)), robotGui, SLOT(updateTheme(QAction*)));

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
