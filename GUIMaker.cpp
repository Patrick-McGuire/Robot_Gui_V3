#include "GUIMaker.h"
#include <iostream>
#include <QTabWidget>
#include <QString>
#include <QMainWindow>

GUIMaker::GUIMaker(QWidget *parent, std::vector<TabInfo*> *config, WidgetData *widgetData, int width, int height) {
    _config = config;
    _parent = parent;
    _widgetData = widgetData;
    _height = height;
    _width = width;

    allWidgets = new std::vector<BaseWidget*>;
    createTab(parent, config);
}

void GUIMaker::createTab(QWidget *parent, std::vector<TabInfo*> *config) {
    auto tabWidget = new QTabWidget(parent);
    tabWidget->setFixedHeight(_height-30);
    tabWidget->setFixedWidth(_width-5);



    for(int i = 0; i < config->size(); i++) {
        if (config[0][i]->isNester) {
            auto *page = new QWidget();
            tabWidget->addTab(page, QString::fromStdString(config[0][i]->name));
            createTab(page, config[0][i]->nestedTabsInfo);
        } else {
            auto *page = new QWidget();
//            std::cout << parent->width() << "\n";
//            page->setFixedSize(parent->width(), parent->height());
            tabWidget->addTab(page, QString::fromStdString(config[0][i]->name));

            page->show();
            std::vector<WidgetInfo*> *widgetInfo;
            widgetInfo = config[0][i]->widgetsInfo;
            for(auto itt = widgetInfo->begin(); itt != widgetInfo->end(); ++itt) {
                if(itt[0]->type == textBoxWidgetSTRID) {
                    auto *textBoxWidget = new TextBoxWidget(page, itt[0], _widgetData);
                    allWidgets->push_back(textBoxWidget);
                } else if(itt[0]->type == videoWidgetSTRID) {
                    auto *vidWid = new VideoWidget(page, itt[0], _widgetData);
                    allWidgets->push_back(vidWid);
                }
            }
        }
    }
}
