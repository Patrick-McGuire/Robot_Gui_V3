#include "SimpleButtonWidget.h"

SimpleButtonWidget::SimpleButtonWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    styledText = true;
    styledWidgetBackgroundColor = true;

    button = new QPushButton(this);
    button->setObjectName(this->objectName() + BUTTON_WIDGET_NAME);
    button->setText(QString::fromStdString(configInfo->title));

    connect(button, SIGNAL(pressed()), this, SLOT(onClick()));
    connect(button, SIGNAL(released()), this, SLOT(onRelease()));
}

void SimpleButtonWidget::onClick() {
    widgetData->raiseOutputFlag(configInfo->id);

    auto json = widgetData->getJsonOutput(configInfo->id);
    json->type = WidgetData::bool_t;
    json->boolVal = true;

    if(!widgetData->outputJsonExists(configInfo->id)) {
        widgetData->setJsonOutput(configInfo->id, json);
    }
}

void SimpleButtonWidget::onRelease() {
    auto json = widgetData->getJsonOutput(configInfo->id);
    json->type = WidgetData::bool_t;
    json->boolVal = false;

    if(!widgetData->outputJsonExists(configInfo->id)) {
        widgetData->setJsonOutput(configInfo->id, json);
    }
}

void SimpleButtonWidget::customUpdateStyle(bool overwrite) {
    std::string textColor = configInfo->textColor;
    std::string backgroundColor = configInfo->backgroundColor;
    if(overwrite || configInfo->textColor == XML_THEME_CONST) {
        textColor = Theme::getTextColorStr(currentTheme);
    }
    if(overwrite || configInfo->backgroundColor == XML_THEME_CONST) {
        if(configInfo->backgroundColor != XML_NONE_CONST) {
            backgroundColor = Theme::getWidgetBackgroundColorStr(currentTheme);
        } else {
            backgroundColor = "transparent";
        }
    } else if(configInfo->backgroundColor == XML_NONE_CONST) {
        backgroundColor = "transparent";
    }

    char buf[400];
    sprintf(buf, "QWidget#%s{ background: %s; color: %s }",
            button->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            textColor.c_str()
    );
    this->setStyleSheet(buf);
}

void SimpleButtonWidget::parseXml(const WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {

}