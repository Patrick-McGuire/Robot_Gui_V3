#include "TabWidget.h"
#include "../CommonFunctions.h"

TabWidget::TabWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    styledBackground = true;
    styledHeader = true;

    this->setLayout(&layout);
    layout.setMargin(0);
    tabs = new QTabWidget();
    layout.addWidget(tabs);
    tabs->setObjectName(QString::fromStdString(configInfo->objectName));
    // Set the size
    int width = configInfo->width == RobotGui::Xml::MAX_CONST_ID || configInfo->width == RobotGui::Xml::AUTO_CONST_ID ? parent->width() : configInfo->width;
    int height = configInfo->height == RobotGui::Xml::MAX_CONST_ID || configInfo->height == RobotGui::Xml::AUTO_CONST_ID ? parent->height() : configInfo->height;
    tabs->setFixedHeight(height);
    tabs->setFixedWidth(width);

    for (int i = 0; i < configInfo->tabNames.size(); i++) {
        // Add new tab to tabWidget and setup it's page
        auto *page = new QWidget();
        page->setObjectName(QString::fromStdString(configInfo->objectName) + "Page"); //+ QString::number(i));
        page->setFixedSize(tabs->width(), tabs->height() - 25);
        tabs->addTab(page, QString::fromStdString(configInfo->tabNames[i]));
        page->show();
        pages.emplace_back(page);

        // Create all widgets in the tab
        for (int j = 0; j < configInfo->tabWidgets[i].size(); j++) {
            configInfo->tabWidgets[i][j]->objectName = configInfo->objectName + "A" + std::to_string(i) + "B" + std::to_string(j);
            widgets.emplace_back(GUIMaker::createWidget(page, configInfo->tabWidgets[i][j], widgetData));
        }
    }

    // This is a hack fix for a bug when first opening up a GUI with nested tabs
    for (int i = 0; i < widgets.size(); i++) {
        tabs->setCurrentIndex(i);
    }
    tabs->setCurrentIndex(0);
}


void TabWidget::updateInFocus() {
    for (auto &widget : widgets) {
        widget->updateData(tabs->currentWidget());
    }
}

void TabWidget::updateNoFocus() {
    for (auto &widget : widgets) {
        widget->updateData(false);
    }
}

void TabWidget::updateOnInFocus() {

}

void TabWidget::customUpdateDraggability(bool _draggable) {
    for (auto &widget : widgets) {
        widget->setDraggability(_draggable);
    }
}

void TabWidget::customUpdateStyle(bool overwrite) {
    std::string tittleTextColor = configInfo->headerColor;
    std::string backgroundColor = configInfo->backgroundColor;
    std::string darkerBackground;

    if (overwrite || configInfo->headerColor == RobotGui::Xml::THEME_CONST) {
        tittleTextColor = Theme::getHeaderTextColorStr(currentTheme);
    }

    if (overwrite || configInfo->backgroundColor == RobotGui::Xml::THEME_CONST) {
        if (configInfo->backgroundColor != RobotGui::Xml::NONE_CONST) {
            backgroundColor = Theme::getBackgroundColorStr(currentTheme);
            auto r_g_b = CommonFunctions::GetRGBFromString(backgroundColor);
            r_g_b[0] = CommonFunctions::Clamp(r_g_b[0] - 10, 0, 255);
            r_g_b[1] = CommonFunctions::Clamp(r_g_b[1] - 10, 0, 255);
            r_g_b[2] = CommonFunctions::Clamp(r_g_b[2] - 10, 0, 255);
            darkerBackground = CommonFunctions::GetStringFromRGB(r_g_b);
        } else {
            backgroundColor = "transparent";
            darkerBackground = backgroundColor;
        }
    } else if (configInfo->backgroundColor == RobotGui::Xml::NONE_CONST) {
        backgroundColor = "transparent";
        darkerBackground = backgroundColor;
    }

    char buf[1000];
    sprintf(buf, "QWidget#%s{ background: %s; } QWidget#%s{ background: %s; } QTabWidget#%s QTabBar::tab{ background: %s; color: %s }",
            this->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            pages[0]->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            this->objectName().toStdString().c_str(),
            darkerBackground.c_str(),
            tittleTextColor.c_str()
    );
    this->setStyleSheet(buf);
}

void TabWidget::updateChildrenStyle(bool overwrite) {
    for (auto &widget : widgets) {
        widget->updateStyle(currentTheme, overwrite);
    }
}

void TabWidget::parseXml(const RobotGui::WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {
    for (auto *tab = node->first_node(); tab; tab = tab->next_sibling()) {                           // Iterate over nodes
        std::string tagName = tab->name();
        if (tagName == RobotGui::Xml::TAB_TAG) {
            std::string tabTitle = "No name";
            for (auto *attr = tab->first_attribute(); attr; attr = attr->next_attribute()) {         // Iterate over attributes
                std::string attrName = attr->name();
                std::string attrVal = attr->value();
                if (attrName == RobotGui::Xml::TITLE_ATR) {
                    tabTitle = attrVal;
                }
            }
            parentConfig->tabNames.emplace_back(tabTitle);
            parseTabChildren(parentConfig, tab);
        }
    }
}

void TabWidget::parseTabChildren(const RobotGui::WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {
    // These calls back to XML input to parse the "sub" widgets
    std::vector<RobotGui::WidgetConfig_ptr> widgetsVec;
    for (auto *widget = node->first_node(); widget; widget = widget->next_sibling()) {
        widgetsVec.emplace_back(XMLInput::parseWidget(widget));
    }
    parentConfig->tabWidgets.emplace_back(widgetsVec);
}
