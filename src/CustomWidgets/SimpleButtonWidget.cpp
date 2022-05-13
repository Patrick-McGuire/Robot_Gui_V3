#include "SimpleButtonWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"
#include "BaseStructure/BaseWidget.h"

RobotGui::SimpleButtonWidget::SimpleButtonWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    styledText = true;
    styledWidgetBackgroundColor = true;
    drawBorder = false;
    configurablePos = true;

    button = new QPushButton(QString::fromStdString(configInfo->title.is_initialized() ? configInfo->title.get() : "err"), this);
    button->adjustSize();
    adjustSize();
    setFixedSize(width() + 5, height() + 5);            // So you can drag
    button->setObjectName(this->objectName() + BUTTON_WIDGET_NAME);

    connect(button, SIGNAL(pressed()), this, SLOT(onClick()));
    connect(button, SIGNAL(released()), this, SLOT(onRelease()));
}

void RobotGui::SimpleButtonWidget::onClick() {
    if(configInfo->source.is_initialized()) {
        widgetData->raiseOutputFlag(configInfo->source.get());
        auto json = widgetData->getOutputJson()->mapGetOrAdd(configInfo->source.get());
        json->setBool(true);
    }
}

void RobotGui::SimpleButtonWidget::onRelease() {
    if(configInfo->source.is_initialized()) {
        auto json = widgetData->getOutputJson()->mapGetOrAdd(configInfo->source.get());
        json->setBool(false);
    }
}

void RobotGui::SimpleButtonWidget::customUpdateStyle() {
    char buf[400];
    sprintf(buf, "QWidget#%s{ background: %s; color: %s }",
            button->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            titleTextColor.c_str()
    );
    this->setStyleSheet(buf);
    adjustSize();
}
