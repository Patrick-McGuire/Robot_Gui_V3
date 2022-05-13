#include "TabWidget.h"
#include "../../../lib/CommonFunctions.h"

#include "../SettingsTab.h"
#include "../../WidgetData.h"
#include "../../GUIMaker.h"
#include "../../Theme.h"
#include "../BaseStructure/BaseWidget.h"
#include "../../Config/XMLOutput.h"

RobotGui::TabWidget::TabWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    styledBackground = true;
    styledHeader = true;
    drawBorder = false;
    configurablePos = true;
    configurableWidth = true;
    configurableHeight = true;

    if(configInfo->type == RobotGui::WidgetConstants::TAB) {
        widgetCollectionConfig = std::dynamic_pointer_cast<WidgetCollectionConfig> (configInfo);
    } else {
        widgetCollectionConfig = WidgetCollectionConfig::create();
    }

    this->setLayout(&layout);
    layout.setMargin(0);
    tabs = new QTabWidget();
    layout.addWidget(tabs);
    tabs->setObjectName(QString::fromStdString(configInfo->objectName));

    if (parent != nullptr) {
        // Set the size
        int width = configInfo->width.is_initialized() ? configInfo->width.get() : RobotGui::Xml::AUTO_CONST_ID;
        int height = configInfo->height.is_initialized() ? configInfo->height.get() : RobotGui::Xml::AUTO_CONST_ID;
        width = width == RobotGui::Xml::MAX_CONST_ID || width == RobotGui::Xml::AUTO_CONST_ID ? parent->width() : width;
        height = height == RobotGui::Xml::MAX_CONST_ID || height == RobotGui::Xml::AUTO_CONST_ID ? parent->height() : height;
        tabs->setFixedHeight(height);
        tabs->setFixedWidth(width);
    }

    for (int i = 0; i < widgetCollectionConfig->tabs.size(); i++) {
        // Add new tab to tabWidget and setup it's page
        auto *page = new QWidget();
        page->setObjectName(QString::fromStdString(configInfo->objectName) + "Page"); //+ QString::number(i));
        page->setFixedSize(tabs->width(), tabs->height() - 25);
        tabs->addTab(page, QString::fromStdString(widgetCollectionConfig->tabs[i].name));
        page->show();
        pages.emplace_back(page);
        widgets.emplace_back(std::vector<BaseWidget *>());

        if (widgetCollectionConfig->tabs[i].widgets.size() == 1 and widgetCollectionConfig->tabs[i].widgets[0]->type == RobotGui::WidgetConstants::TAB) { //If we're doing a settings tab, parse a little differently
            //Make the widget
            BaseWidget *newWidget = new SettingsTab(page, widgetCollectionConfig->tabs[i].widgets[0], widgetData, theme);
            widgets[i].emplace_back(newWidget);

            //Make a layout for this tab and add the widget to that layout
            auto layout_2 = new QGridLayout();
            layout_2->addWidget(newWidget);
            layout_2->setMargin(0);
            page->setLayout(layout_2);
        } else {
            // Create all widgets in the tab
            for (int j = 0; j < widgetCollectionConfig->tabs[i].widgets.size(); j++) {
                widgetCollectionConfig->tabs[i].widgets[j]->objectName = configInfo->objectName + "A" + std::to_string(i) + "B" + std::to_string(j);
                auto newWidget = RobotGui::GUIMaker::createWidget(page, widgetCollectionConfig->tabs[i].widgets[j], widgetData, theme);
                if (newWidget != nullptr) {
                    widgets[i].emplace_back(newWidget);
                }
            }
        }
    }

    // This is a hack fix for a bug when first opening up a GUI with nested tabs
//    for (int i = 0; i < widgets.size(); i++) {
//        tabs->setCurrentIndex(i);
//    }
    tabs->setCurrentIndex(0);
}

void RobotGui::TabWidget::updateInFocus() {
    for (auto &tab : widgets) {
        for (auto &widget: tab) {
            widget->updateData(tabs->currentWidget());
        }
    }
}

void RobotGui::TabWidget::updateNoFocus() {
    for (auto &tab : widgets) {
        for (auto &widget : tab) {
            widget->updateData(false);
        }
    }
}

void RobotGui::TabWidget::updateOnInFocus() {

}

void RobotGui::TabWidget::customUpdateDraggability(bool _draggable) {
    for (auto &tab : widgets) {
        for (auto &widget: tab) {
            widget->setDraggability(_draggable);
        }
    }
}

void RobotGui::TabWidget::customUpdateStyle() {
    std::string textColor = CommonFunctions::GetContrastingTextColor(backgroundColor);
    std::string darkerBackground = CommonFunctions::GenerateDarkerColor(backgroundColor, 10);;
    std::string darkerDarkerBorder = CommonFunctions::GenerateDarkerColor(darkerBackground, 10);
    std::string newBorderColor = "rgb(50,50,50)";

    std::string stylesheetString = std::string("QTabWidget::pane { border: 1px solid " + newBorderColor + ";}") +
                                   "QTabWidget::tab-bar {left: 0px; }" +
                                   "QTabBar::tab {background: " + darkerBackground + "; color: " + textColor + ";border: 1px solid " + newBorderColor + ";border-bottom-color: " + darkerDarkerBorder + "; border-top-left-radius: 2px;border-top-right-radius: 2px;min-width: 8ex;padding: 2px;}" +
                                   "QTabBar::tab:selected, QTabBar::tab:hover {background: " + darkerBackground + "}" +
                                   "QTabBar::tab:selected {border-color: " + newBorderColor + ";border-bottom-color: " + darkerDarkerBorder + "; }" +
                                   "QTabBar::tab:!selected {margin-top: 2px;}";

    tabs->setStyleSheet(QString::fromStdString(stylesheetString));
    this->setStyleSheet("QWidget#" + objectName() + "{ background: " + QString::fromStdString(backgroundColor) + "}");
    for (auto &page : pages) {
        page->setStyleSheet("QWidget#" + pages[0]->objectName() + "{ background: " + QString::fromStdString(backgroundColor) + "}");
    }
}

void RobotGui::TabWidget::updateChildrenStyle() {
    for (auto &tab : widgets) {
        for (auto &widget: tab) {
            widget->updateStyle();
        }
    }
}


RobotGui::TabWidget::~TabWidget() {
    for (auto &tab : widgets) {
        for (auto &widget: tab) {
            delete widget;
        }
    }
}

