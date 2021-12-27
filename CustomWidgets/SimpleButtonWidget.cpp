#include "SimpleButtonWidget.h"

SimpleButtonWidget::SimpleButtonWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    styledText = true;
    styledWidgetBackgroundColor = true;
    drawBorder = false;

    button = new QPushButton(QString::fromStdString(configInfo->title), this);
//    button->setFixedWidth(300);
//    button->setSizePolicy(QSizePolicy::, QSizePolicy::Expanding);
    button->setObjectName(this->objectName() + BUTTON_WIDGET_NAME);

    connect(button, SIGNAL(pressed()), this, SLOT(onClick()));
    connect(button, SIGNAL(released()), this, SLOT(onRelease()));
}

void SimpleButtonWidget::onClick() {
    widgetData->raiseOutputFlag(configInfo->id);

    auto json = widgetData->getJsonOutput(configInfo->id);
    json->type = WidgetData::bool_t;
    json->boolVal = true;

    if (!widgetData->outputJsonExists(configInfo->id)) {
        widgetData->setJsonOutput(configInfo->id, json);
    }
}

void SimpleButtonWidget::onRelease() {
    auto json = widgetData->getJsonOutput(configInfo->id);
    json->type = WidgetData::bool_t;
    json->boolVal = false;

    if (!widgetData->outputJsonExists(configInfo->id)) {
        widgetData->setJsonOutput(configInfo->id, json);
    }
}

void SimpleButtonWidget::customUpdateStyle(const std::string &backgroundColor, const std::string &widgetBackgroundColor, const std::string &bodyTextColor, const std::string &titleTextColor, const std::string &borderColor) {
    char buf[400];
    sprintf(buf, "QWidget#%s{ background: %s; color: %s }",
            button->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            bodyTextColor.c_str()
    );
    this->setStyleSheet(buf);
}

void SimpleButtonWidget::parseXml(const RobotGui::WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {

}