#include "MenuWidget.h"
#include "../CommonFunctions.h"

MenuWidget::MenuWidget(QWidget *parent, AppConfig *appConfig_, CoreGui *coreGui, GuiInstance *robotGui, Theme *_theme) : QMenuBar(parent) {
    theme = _theme;
    appConfig = appConfig_;
    // File menu
    auto *file = new QMenu("File");
    file->setObjectName(FILE_MENU_NAME);
    menus.emplace_back(file);
    file->addAction("Open", coreGui, SLOT(openReload()));
    file->addAction("Reload", coreGui, SLOT(reload()));
    file->addAction("Reparse", coreGui, SLOT(reparseReload()));
    // Settings menu
    auto *settings = new QMenu("Settings");
    settings->setObjectName(SETTINGS_MENU_NAME);
    menus.emplace_back(settings);
    settings->addAction("Make all draggable", robotGui, SLOT(makeWidgetsDraggable()));
    settings->addAction("Make all fixed", robotGui, SLOT(makeWidgetsFixed()));
    // Theme2 menu
    auto *theme = new QMenu("Theme2");
    theme->setObjectName(THEME_MENU_NAME);
    menus.emplace_back(theme);
    auto *setTheme = theme->addMenu("Set theme");
    menus.emplace_back(setTheme);
    setTheme->setObjectName(QString(THEME_MENU_NAME) + "1");

    auto *subMenuAct1 = setTheme->addAction(QString::fromStdString(Theme::getThemeName(RobotGui::Themes::DARK)));
    subMenuAct1->setData(QString::fromStdString(Theme::getThemeName(RobotGui::Themes::DARK)));
    auto *subMenuAct2 = setTheme->addAction(QString::fromStdString(Theme::getThemeName(RobotGui::Themes::LIGHT)));
    subMenuAct2->setData(QString::fromStdString(Theme::getThemeName(RobotGui::Themes::LIGHT)));
    auto *subMenuAct3 = setTheme->addAction(QString::fromStdString(Theme::getThemeName(RobotGui::Themes::GREEN)));
    subMenuAct3->setData(QString::fromStdString(Theme::getThemeName(RobotGui::Themes::GREEN)));

    connect(setTheme, SIGNAL(triggered(QAction * )), robotGui, SLOT(updateTheme(QAction * )));

    theme->addMenu(setTheme);

    // Finishing up
    this->addMenu(file);
    this->addMenu(settings);
    this->addMenu(theme);
}


void MenuWidget::updateTheme() {
    QString style = "";
    auto darkerBackground = CommonFunctions::GenerateDarkerColor(theme->getBackgroundColor(), 10);
    auto textColor = CommonFunctions::GetContrastingTextColor(theme->getBackgroundColor());
    auto lighterColor = CommonFunctions::GenerateDarkerColor(theme->getBackgroundColor(), -10);

    style += QString("background: ") + QString::fromStdString(darkerBackground) + ";";
    style += "color: " + QString::fromStdString(textColor) + ";";
    this->setStyleSheet(style);

    for (auto &element : menus) {
        style = "QMenu#" + element->objectName() + "{background-color : " + QString::fromStdString(lighterColor) + "; color : " + QString::fromStdString(textColor) + "}" +
                "QMenu::item:selected#" + element->objectName() + "{background-color :" + QString::fromStdString(theme->getHighlightColor()) + "}";
        element->setStyleSheet(style);
    }
}
