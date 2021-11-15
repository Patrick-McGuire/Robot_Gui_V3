//
// Created by patrick on 11/6/21.
//

#include "TabWidget.h"

TabWidget::TabWidget(QWidget *parent, WidgetConfig_ptr configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    this->setLayout(&layout);
    layout.setMargin(0);
    tabs = new QTabWidget();
    tabs->setFixedHeight(configInfo->height-30);
    tabs->setFixedWidth(configInfo->width-5);
    layout.addWidget(tabs);

    for(int i = 0; i < configInfo->tabNames.size(); i++) {
        // Add new tab to tabWidget and setup it's page
        auto *page = new QWidget();
        tabs->addTab(page, QString::fromStdString(configInfo->tabNames[i]));
        page->show();
        pages.emplace_back(page);

        // Create all widgets in the tab
        for(auto & j : configInfo->tabWidgets[i]) {
            widgets.emplace_back(GUIMaker::createWidget(page, j, widgetData));
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
}


void TabWidget::updateInFocus() {
    for(int i = 0; i < widgets.size(); i++) {
        widgets[i]->updateData(tabs->currentWidget());
    }
}

void TabWidget::updateNoFocus() {

}

void TabWidget::updateOnInFocus() {

}

void TabWidget::parseXml(WidgetConfig_ptr parentConfig, rapidxml::xml_node<> *node) {
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

void TabWidget::parseTabChildren(WidgetConfig_ptr parentConfig, rapidxml::xml_node<> *node) {
    //// This calls back to XML input to parse the "sub" widgets ////
    std::vector<WidgetConfig_ptr> widgetsVec;
    for(auto *widget = node->first_node(); widget; widget = widget->next_sibling()) {
        widgetsVec.emplace_back(XMLInput::parseWidget(widget));
    }
    parentConfig->tabWidgets.emplace_back(widgetsVec);
}