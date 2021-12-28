//
// Created by nathan on 12/28/21.
//

#include "CompleteConsoleWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

#include "SimpleConsoleWidget.h"

CompleteConsoleWidget::CompleteConsoleWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    auto newConfigInfo = std::make_shared<RobotGui::WidgetConfig>();
    newConfigInfo->source = configInfo->source;
    newConfigInfo->backgroundColor = configInfo->backgroundColor;
    newConfigInfo->foregroundColor = configInfo->foregroundColor;
    newConfigInfo->textColor = configInfo->textColor;
    newConfigInfo->headerColor = configInfo->headerColor;

    titleWidget = new QLabel();
    textEntryWidget = new QLineEdit();
    simpleConsoleWidget = new SimpleConsoleWidget(nullptr, newConfigInfo, widgetData, theme, false);

    auto layout = new QGridLayout();
    layout->addWidget(titleWidget);
    layout->addWidget(textEntryWidget);
    layout->addWidget(simpleConsoleWidget);
    setLayout(layout);

    titleWidget->setText(QString::fromStdString(configInfo->title));
    titleWidget->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    adjustSize();
}

void CompleteConsoleWidget::updateInFocus() {
    simpleConsoleWidget->update();
    simpleConsoleWidget->adjustSize();
    adjustSize();
}

void CompleteConsoleWidget::customUpdateStyle() {
    titleWidget->setFont(font());
    textEntryWidget->setFont(font());

    titleWidget->setStyleSheet(QString::fromStdString("color: " + titleTextColor));
    textEntryWidget->setStyleSheet(QString::fromStdString("border: 1px solid " + borderColor + "; color: " + bodyTextColor + "; background: " + widgetBackgroundColor));
    simpleConsoleWidget->customUpdateStyle();
}


