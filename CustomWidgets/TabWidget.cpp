#include "TabWidget.h"
#include "../CommonFunctions.h"

TabWidget::TabWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    styledBackground = true;
    styledHeader = true;
    drawBorder=false;

    this->setLayout(&layout);
    layout.setMargin(0);
    tabs = new QTabWidget();
    layout.addWidget(tabs);
    tabs->setObjectName(QString::fromStdString(configInfo->objectName));
    // Set the size
    int width = configInfo->width == xmlMaxConstID || configInfo->width == xmlAutoConstID ? parent->width() : configInfo->width;
    int height = configInfo->height == xmlMaxConstID || configInfo->height == xmlAutoConstID ? parent->height() : configInfo->height;
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
    std::string textColor = "rgb(0,0,0)";
    std::string borderColor = "rgb(50,50,50)";
    std::string darkerBackground;
    std::string darkerDarkerBorder;

    if (overwrite || configInfo->headerColor == xmlThemeConst) {
        tittleTextColor = Theme::getHeaderTextColorStr(currentTheme);
    }

    if (overwrite || configInfo->backgroundColor == xmlThemeConst) {
        if (configInfo->backgroundColor != xmlNoneConst) {
            backgroundColor = Theme::getBackgroundColorStr(currentTheme);
            darkerBackground = CommonFunctions::GenerateDarkerColor(backgroundColor, 10);
            darkerDarkerBorder = CommonFunctions::GenerateDarkerColor(darkerBackground, 10);
            textColor = CommonFunctions::GetContrastingTextColor(backgroundColor);
        } else {
            backgroundColor = "transparent";
            darkerBackground = backgroundColor;
            darkerDarkerBorder = backgroundColor;
        }
    } else if (configInfo->backgroundColor == xmlNoneConst) {
        backgroundColor = "transparent";
        darkerBackground = backgroundColor;
        darkerDarkerBorder = backgroundColor;
    }

    std::string stylesheetString = std::string("QTabWidget::pane { border: 1px solid " + borderColor + ";}") +
                                   "QTabWidget::tab-bar {left: 5px; }" +
                                   "QTabBar::tab {background: " + darkerBackground + "; color: " + textColor + ";border: 1px solid " + borderColor + ";border-bottom-color: " + darkerDarkerBorder + "; border-top-left-radius: 2px;border-top-right-radius: 2px;min-width: 8ex;padding: 2px;}" +
                                   "QTabBar::tab:selected, QTabBar::tab:hover {background: " + darkerBackground + "}" +
                                   "QTabBar::tab:selected {border-color: " + borderColor + ";border-bottom-color: " + darkerDarkerBorder + "; }" +
                                   "QTabBar::tab:!selected {margin-top: 2px;}";

    tabs->setStyleSheet(QString::fromStdString(stylesheetString));
    this->setStyleSheet("QWidget#" + objectName() + "{ background: " + QString::fromStdString(backgroundColor) + "}");
    for (auto &page : pages) {
        page->setStyleSheet("QWidget#" + pages[0]->objectName() + "{ background: " + QString::fromStdString(backgroundColor) + "}");
    }
}

void TabWidget::updateChildrenStyle(bool overwrite) {
    for (auto &widget : widgets) {
        widget->updateStyle(currentTheme, overwrite);
    }
}

void TabWidget::parseXml(const WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {
    for (auto *tab = node->first_node(); tab; tab = tab->next_sibling()) {                           // Iterate over nodes
        std::string tagName = tab->name();
        if (tagName == XML_TAB_TAG) {
            std::string tabTitle = "No name";
            for (auto *attr = tab->first_attribute(); attr; attr = attr->next_attribute()) {         // Iterate over attributes
                std::string attrName = attr->name();
                std::string attrVal = attr->value();
                if (attrName == XML_TITLE_ATR) {
                    tabTitle = attrVal;
                }
            }
            parentConfig->tabNames.emplace_back(tabTitle);
            parseTabChildren(parentConfig, tab);
        }
    }
}

void TabWidget::parseTabChildren(const WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {
    // These calls back to XML input to parse the "sub" widgets
    std::vector<WidgetConfig_ptr> widgetsVec;
    for (auto *widget = node->first_node(); widget; widget = widget->next_sibling()) {
        widgetsVec.emplace_back(XMLInput::parseWidget(widget));
    }
    parentConfig->tabWidgets.emplace_back(widgetsVec);
}
