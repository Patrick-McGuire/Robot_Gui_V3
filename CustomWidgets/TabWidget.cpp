//
// Created by patrick on 11/6/21.
//

#include "TabWidget.h"

TabWidget::TabWidget(QWidget *parent, WidgetConfig *configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    this->setLayout(&layout);
    layout.setMargin(0);
    tabs = new QTabWidget();
    tabs->setFixedHeight(configInfo->height-30);
    tabs->setFixedWidth(configInfo->width-5);
    layout.addWidget(tabs);
    tabs->show();
//    setPosition(configInfo->x, configInfo->y);
//    this->move(configInfo->x, configInfo->y);

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

void TabWidget::parseXml(struct WidgetConfig *parentConfig, rapidxml::xml_node<> *node) {
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

void TabWidget::parseTabChildren(struct WidgetConfig *parentConfig, rapidxml::xml_node<> *node) {
    //// This calls back to XML input to parse the "sub" widgets ////
    std::vector<struct WidgetConfig*> widgetsVec;
    for(auto *widget = node->first_node(); widget; widget = widget->next_sibling()) {
        widgetsVec.emplace_back(XMLInput::parseWidget(widget));
    }
    parentConfig->tabWidgets.emplace_back(widgetsVec);
}