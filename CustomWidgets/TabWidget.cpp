//
// Created by patrick on 11/6/21.
//

#include "TabWidget.h"

TabWidget::TabWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
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

    for(int i = 0; i < configInfo->tabNames.size(); i++) {
        // Add new tab to tabWidget and setup it's page
        auto *page = new QWidget();
        page->setFixedSize(tabs->width(), tabs->height()-25);
        tabs->addTab(page, QString::fromStdString(configInfo->tabNames[i]));
        page->show();
        pages.emplace_back(page);

        // Create all widgets in the tab
        for(int j = 0; j < configInfo->tabWidgets[i].size(); j++) {
            configInfo->tabWidgets[i][j]->objectName = configInfo->objectName + "A" + std::to_string(i) + "B" + std::to_string(j);
            widgets.emplace_back(GUIMaker::createWidget(page, configInfo->tabWidgets[i][j], widgetData));
        }
    }
    // Just don't even ask
    // Please don't ask
    // Fine. It's a dumb fix for a problem that makes no sense
    // Comment this out, configure nested tabs, and enjoy
    for(int i = 0; i < widgets.size(); i++) {
        tabs->setCurrentIndex(i);
    }
    tabs->setCurrentIndex(0);

//    std::cout << tabs->objectName().toStdString() << "\n";
//    if(this->objectName() != "1") {
//        tabs->setObjectName(QString::fromStdString("asdfasfd"));
//        std::cout << tabs->objectName().toStdString() << " f\n";
//        this->setStyleSheet(QString("QTabWidget::QTabBar#") + tabs->objectName() + " { background: rgb(125,125,125) } ");
//        tabs->tabBar()->setStyleSheet();
//        this->setStyleSheet(QString("QTabBar") + " { background: rgb(125,125,125) } ");
//    }
}


void TabWidget::updateInFocus() {
    for(auto & widget : widgets) {
        widget->updateData(tabs->currentWidget());
    }
}

void TabWidget::updateNoFocus() {
    for(auto & widget : widgets) {
        widget->updateData(false);
    }
}

void TabWidget::updateOnInFocus() {

}

void TabWidget::parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node) {
    for(auto *tab = node->first_node(); tab; tab = tab->next_sibling()) {                           // Iterate over nodes
        std::string tagName = tab->name();
        if(tagName == xmlTabTag) {
            std::string tabTitle = "No name";
            for(auto *attr = tab->first_attribute(); attr; attr = attr->next_attribute()) {         // Iterate over attributes
                std::string attrName = attr->name();
                std::string attrVal = attr->value();
                if(attrName == xmlTitleATR) {
                    tabTitle = attrVal;
                }
            }
            parentConfig->tabNames.emplace_back(tabTitle);
            parseTabChildren(parentConfig, tab);
        }
    }
}

void TabWidget::parseTabChildren(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node) {
    //// This calls back to XML input to parse the "sub" widgets ////
    std::vector<WidgetConfig_ptr> widgetsVec;
    for(auto *widget = node->first_node(); widget; widget = widget->next_sibling()) {
        widgetsVec.emplace_back(XMLInput::parseWidget(widget));
    }
    parentConfig->tabWidgets.emplace_back(widgetsVec);
}

void TabWidget::customUpdateDraggability(bool _draggable) {
    for(auto & widget : widgets) {
        widget->setDraggability(_draggable);
    }
}

void TabWidget::updateTheme(Themes _theme, bool overwrite) {
    QString style = "";
    // Set the background color
    if(overwrite || _configInfo->backgroundColor == xmlThemeConst) {
        style += QString("background: ") + QString::fromStdString(Theme::getBackgroundColorStr(_theme)) + ";"; //Theme::getBackgroundColorStr(_theme)
    } else if(_configInfo->backgroundColor != xmlThemeConst || _configInfo->backgroundColor != xmlNoneConst) {
        style += QString("background: ") + QString::fromStdString(_configInfo->backgroundColor) + ";";
    }
    // Set the text color
    if(overwrite || _configInfo->textColor == xmlThemeConst) {
        style += "color: " + QString::fromStdString(Theme::getHeaderTextColorStr(_theme)) + ";";
    } else if(_configInfo->textColor != xmlThemeConst) {
        style += QString("color: ") + QString::fromStdString(_configInfo->textColor) + ";";
    }

    for(auto & widget : widgets) {
        widget->updateTheme(_theme, overwrite);
    }
    this->setStyleSheet(style);
}
