#include "GUIMaker.h"
#include <iostream>
#include <QTabWidget>
#include <QString>

GUIMaker::GUIMaker(QWidget *parent, std::vector<TabInfo*> *config, WidgetData *widgetData) {
    _config = config;
    _parent = parent;
    _widgetData = widgetData;
    tabWidget = new QTabWidget(parent);
    tabWidget->setFixedHeight(1000);
    tabWidget->setFixedWidth(1000);
    allWidgets = new std::vector<BaseWidget*>;
    createTab(config);
}

void GUIMaker::createTab(std::vector<TabInfo*> *config) {
    for(auto it = _config->begin(); it != _config->end(); ++it) {
        if (it[0]->isNester) {
            createTab(it[0]->nestedTabsInfo);
        } else {
            auto *page = new QWidget();
            tabWidget->addTab(page, QString::fromStdString(*it[0]->name));

            page->show();
            std::vector<WidgetInfo*> *widgetInfo;
            widgetInfo = it[0]->widgetsInfo;
            for(auto itt = widgetInfo->begin(); itt != widgetInfo->end(); ++itt) {
                auto *textBoxWidget = new TextBoxWidget(page, itt[0], _widgetData);
                allWidgets->push_back(textBoxWidget);
            }
        }
    }
}
