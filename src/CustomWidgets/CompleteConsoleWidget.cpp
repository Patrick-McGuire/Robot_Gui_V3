#include "CompleteConsoleWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

#include "SimpleConsoleWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"
#include "BaseStructure/BaseWidget.h"
#include "BaseStructure/WidgetBaseConfig.h"
#include "../Config/XMLInput.h"

RobotGui::CompleteConsoleWidget::CompleteConsoleWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    ////// NATHAN WTF IS GOING ON HERE THIS CODE IS ASS

    auto newConfigInfo = WidgetBaseConfig::create();
    newConfigInfo = WidgetBaseConfig::create(RobotGui::WidgetConstants::SIMPLE_CONSOLE);
    newConfigInfo->source = configInfo->source.is_initialized() ? configInfo->source.get() : "";
    newConfigInfo->backgroundColor = configInfo->backgroundColor.is_initialized() ? configInfo->backgroundColor.get() : RobotGui::Xml::THEME_CONST;
    newConfigInfo->foregroundColor = configInfo->backgroundColor.is_initialized() ? configInfo->foregroundColor.get() : RobotGui::Xml::THEME_CONST;
    newConfigInfo->textColor = configInfo->backgroundColor.is_initialized() ? configInfo->textColor.get() : RobotGui::Xml::THEME_CONST;
    newConfigInfo->headerColor = configInfo->backgroundColor.is_initialized() ? configInfo->headerColor.get() : RobotGui::Xml::THEME_CONST;
    newConfigInfo->staticPos = true;

    titleWidget = new QLabel();
    textEntryWidget = new QLineEdit();
    simpleConsoleWidget = new RobotGui::SimpleConsoleWidget(nullptr, newConfigInfo, widgetData, theme, false);

    auto layout = new QGridLayout();
    layout->addWidget(titleWidget);
    layout->addWidget(textEntryWidget);
    layout->addWidget(simpleConsoleWidget);
    setLayout(layout);

    titleWidget->setText(configInfo->title.is_initialized() ? configInfo->title->c_str() : "err");
    titleWidget->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    titleWidget->setFont(font());
    textEntryWidget->setFont(font());
    simpleConsoleWidget->setFont(QFont("Monospace", font().pointSize()));

    adjustSize();
}

void RobotGui::CompleteConsoleWidget::updateInFocus() {
    simpleConsoleWidget->update();
    simpleConsoleWidget->adjustSize();
    adjustSize();
}

void RobotGui::CompleteConsoleWidget::customUpdateStyle() {
    titleWidget->setFont(font());
    textEntryWidget->setFont(font());
    simpleConsoleWidget->setFont(QFont("Monospace", font().pointSize()));

    titleWidget->setStyleSheet(QString::fromStdString("color: " + getHeaderColor()));
    textEntryWidget->setStyleSheet(QString::fromStdString("border: 1px solid " + getBorderColor() + "; color: " + getTextColor() + "; background: " + getWidgetBackgroundColor()));
    simpleConsoleWidget->customUpdateStyle();
}


