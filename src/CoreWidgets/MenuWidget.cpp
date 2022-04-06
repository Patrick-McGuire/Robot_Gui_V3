#include "MenuWidget.h"
#include "../../lib/CommonFunctions.h"
#include "../GuiInstance.h"
#include "../Theme.h"

MenuWidget::MenuWidget(QWidget *parent, AppConfig *appConfig_, RobotGui::GuiCore *coreGui, RobotGui::GuiInstance *robotGui, RobotGui::Theme *_theme) : QMenuBar(parent) {
    theme = _theme;
    appConfig = appConfig_;
    // File menu
    auto *file = new QMenu("File");
    file->setObjectName(FILE_MENU_NAME);
    menus.emplace_back(file);
    file->addAction("Open", coreGui, SLOT(openReload()));
    file->addAction("Reload", coreGui, SLOT(reload()));
    file->addAction("Reparse", coreGui, SLOT(reparseReload()));
    file->addAction("Save", robotGui, SLOT(save()));
    file->addAction("Save as", robotGui, SLOT(saveAs()));
    // Settings menu
    auto *settings = new QMenu("Settings");
    settings->setObjectName(SETTINGS_MENU_NAME);
    menus.emplace_back(settings);
    settings->addAction("Make all draggable", robotGui, SLOT(makeWidgetsDraggable()));
    settings->addAction("Make all fixed", robotGui, SLOT(makeWidgetsFixed()));
    // Theme2 menu
    auto *themeMenu = new QMenu("Theme");
    themeMenu->setObjectName(THEME_MENU_NAME);
    menus.emplace_back(themeMenu);

    auto *subMenuAct1 = themeMenu->addAction(QString::fromStdString(RobotGui::Theme::getThemeName(RobotGui::Themes::DARK)));
    subMenuAct1->setData(QString::fromStdString(RobotGui::Theme::getThemeName(RobotGui::Themes::DARK)));
    auto *subMenuAct2 = themeMenu->addAction(QString::fromStdString(RobotGui::Theme::getThemeName(RobotGui::Themes::LIGHT)));
    subMenuAct2->setData(QString::fromStdString(RobotGui::Theme::getThemeName(RobotGui::Themes::LIGHT)));
    auto *subMenuAct3 = themeMenu->addAction(QString::fromStdString(RobotGui::Theme::getThemeName(RobotGui::Themes::GREEN)));
    subMenuAct3->setData(QString::fromStdString(RobotGui::Theme::getThemeName(RobotGui::Themes::GREEN)));
    auto *subMenuAct4 = themeMenu->addAction(QString::fromStdString(RobotGui::Theme::getThemeName(RobotGui::Themes::RED)));
    subMenuAct4->setData(QString::fromStdString(RobotGui::Theme::getThemeName(RobotGui::Themes::RED)));

    connect(themeMenu, SIGNAL(triggered(QAction * )), robotGui, SLOT(updateTheme(QAction * )));

    // Finishing up
    this->addMenu(file);
    this->addMenu(settings);
    this->addMenu(themeMenu);
}


void MenuWidget::updateTheme() {
    QString style = "";
    auto darkerBackground = CommonFunctions::GenerateDarkerColor(theme->getBackgroundColor(), 10);
    auto textColor = CommonFunctions::GetContrastingTextColor(theme->getBackgroundColor());
    auto lighterColor = CommonFunctions::GenerateDarkerColor(theme->getBackgroundColor(), -10);

    style += QString("background: ") + QString::fromStdString(darkerBackground) + ";";
    style += "color: " + QString::fromStdString(textColor) + ";";
    this->setStyleSheet(style);

    for (auto &element: menus) {
        style = "QMenu#" + element->objectName() + "{background-color : " + QString::fromStdString(lighterColor) + "; color : " + QString::fromStdString(textColor) + "}" +
                "QMenu::item:selected#" + element->objectName() + "{background-color :" + QString::fromStdString(theme->getHighlightColor()) + "}";
        element->setStyleSheet(style);
    }
}
