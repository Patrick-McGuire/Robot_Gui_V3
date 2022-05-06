//
// Created by nathan on 12/28/21.
//

#include "CompleteConsoleWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

#include "SimpleConsoleWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"
#include "BaseWidgetHelper/BaseWidget.h"

RobotGui::CompleteConsoleWidget::CompleteConsoleWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    auto newConfigInfo = std::make_shared<RobotGui::WidgetConfig>();
    newConfigInfo->source = configInfo->source;
    newConfigInfo->backgroundColor = configInfo->backgroundColor;
    newConfigInfo->foregroundColor = configInfo->foregroundColor;
    newConfigInfo->textColor = configInfo->textColor;
    newConfigInfo->headerColor = configInfo->headerColor;
    newConfigInfo->staticPos = true;

    titleWidget = new QLabel();
    textEntryWidget = new QLineEdit();
    simpleConsoleWidget = new RobotGui::SimpleConsoleWidget(nullptr, newConfigInfo, widgetData, theme, false);

    auto layout = new QGridLayout();
    layout->addWidget(titleWidget);
    layout->addWidget(textEntryWidget);
    layout->addWidget(simpleConsoleWidget);
    setLayout(layout);

    titleWidget->setText(QString::fromStdString(configInfo->title));
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

    titleWidget->setStyleSheet(QString::fromStdString("color: " + titleTextColor));
    textEntryWidget->setStyleSheet(QString::fromStdString("border: 1px solid " + borderColor + "; color: " + bodyTextColor + "; background: " + widgetBackgroundColor));
    simpleConsoleWidget->customUpdateStyle();
}


