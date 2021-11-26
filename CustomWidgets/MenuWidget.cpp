#include "MenuWidget.h"

MenuWidget::MenuWidget(QWidget *parent, AppConfig *appConfig_, CoreGUI *coreGui, RobotGUI *robotGui) : QMenuBar(parent) {
    appConfig = appConfig_;
    // File menu
    auto *file = new QMenu("File");
    file->setObjectName(fileMenuName);
    menus.emplace_back(file);
    file->addAction("Open", coreGui, SLOT(openReload()));
    file->addAction("Reload", coreGui, SLOT(reload()));
    file->addAction("Reparse", coreGui, SLOT(reparseReload()));
    // Settings menu
    auto *settings = new QMenu("Settings");
    settings->setObjectName(settingsMenuName);
    menus.emplace_back(settings);
    settings->addAction("Make all draggable", robotGui, SLOT(makeWidgetsDraggable()));
    settings->addAction("Make all fixed", robotGui, SLOT(makeWidgetsFixed()));
    // Theme menu
    auto *theme = new QMenu("Theme");
    theme->setObjectName(themeMenuName);
    menus.emplace_back(theme);
    auto *setTheme = theme->addMenu("Set theme");
    menus.emplace_back(setTheme);
    setTheme->setObjectName(QString(themeMenuName) + "1");

    auto *subMenuAct1 = setTheme->addAction(QString::fromStdString(Theme::getThemeName(Themes::Dark)));
    subMenuAct1->setData(QString::fromStdString(Theme::getThemeName(Themes::Dark)));
    auto *subMenuAct2 = setTheme->addAction(QString::fromStdString(Theme::getThemeName(Themes::Light)));
    subMenuAct2->setData(QString::fromStdString(Theme::getThemeName(Themes::Light)));
    auto *subMenuAct3 = setTheme->addAction(QString::fromStdString(Theme::getThemeName(Themes::Green)));
    subMenuAct3->setData(QString::fromStdString(Theme::getThemeName(Themes::Green)));

    connect(setTheme, SIGNAL(triggered(QAction*)), robotGui, SLOT(updateTheme(QAction*)));

    theme->addMenu(setTheme);
    auto *setAll = theme->addMenu("Set theme for all");
    menus.emplace_back(setAll);
    setAll->setObjectName(QString(themeMenuName) + "2");

    auto *subMenuAct11 = setAll->addAction(QString::fromStdString(Theme::getThemeName(Themes::Dark)));
    subMenuAct11->setData(QString::fromStdString(Theme::getThemeName(Themes::Dark)));
    auto *subMenuAct22 = setAll->addAction(QString::fromStdString(Theme::getThemeName(Themes::Light)));
    subMenuAct22->setData(QString::fromStdString(Theme::getThemeName(Themes::Light)));
    auto *subMenuAct33 = setAll->addAction(QString::fromStdString(Theme::getThemeName(Themes::Green)));
    subMenuAct33->setData(QString::fromStdString(Theme::getThemeName(Themes::Green)));

    connect(setAll, SIGNAL(triggered(QAction*)), robotGui, SLOT(forceTheme(QAction*)));

    theme->addMenu(setAll);
    // Finishing up
    this->addMenu(file);
    this->addMenu(settings);
    this->addMenu(theme);
}


void MenuWidget::updateTheme(Themes _theme) {
    QString style = "";

    style += QString("background: ") + QString::fromStdString(Theme::getBackgroundColorStr(_theme)) + ";"; //Theme::getBackgroundColorStr(_theme)
    style += "color: " + QString::fromStdString(Theme::getHeaderTextColorStr(_theme)) + ";";
    this->setStyleSheet(style);

    for(auto & element : menus) {
        style =
            "QMenu#" + element->objectName() + "{"
                "background-color : " + QString::fromStdString(Theme::getBackgroundColorStr(_theme)) +
            "; color : " + QString::fromStdString(Theme::getTextColorStr(_theme)) +
            "}" + "QMenu::item:selected#" + element->objectName() + "{"
                "background-color :" + QString::fromStdString(Theme::getRightClickMenuHighlightColorStr(_theme)) +
            "}";
        element->setStyleSheet(style);
    }
}
