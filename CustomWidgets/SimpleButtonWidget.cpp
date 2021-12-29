#include "SimpleButtonWidget.h"

SimpleButtonWidget::SimpleButtonWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    styledText = true;
    styledWidgetBackgroundColor = true;
    drawBorder = false;
    configurablePos = true;

    button = new QPushButton(QString::fromStdString(configInfo->title), this);
    adjustSize();
//    button->setFixedWidth(300);
//    button->setSizePolicy(QSizePolicy::, QSizePolicy::Expanding);
    button->setObjectName(this->objectName() + BUTTON_WIDGET_NAME);

    connect(button, SIGNAL(pressed()), this, SLOT(onClick()));
    connect(button, SIGNAL(released()), this, SLOT(onRelease()));
}

void SimpleButtonWidget::onClick() {
    widgetData->raiseOutputFlag(configInfo->id);

    auto json = widgetData->getJsonOutput(configInfo->id);
    json->setBool(true);
//    json->type = WidgetData::bool_t;
//    json->boolVal = true;

    if (!widgetData->outputJsonExists(configInfo->id)) {
        widgetData->setJsonOutput(configInfo->id, json);
    }
}

void SimpleButtonWidget::onRelease() {
    auto json = widgetData->getJsonOutput(configInfo->id);
    json->setBool(false);
//    json->type = WidgetData::bool_t;
//    json->boolVal = false;

    if (!widgetData->outputJsonExists(configInfo->id)) {
        widgetData->setJsonOutput(configInfo->id, json);
    }
}

void SimpleButtonWidget::customUpdateStyle() {
    char buf[400];
    sprintf(buf, "QWidget#%s{ background: %s; color: %s }",
            button->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            titleTextColor.c_str()
    );
    this->setStyleSheet(buf);
    adjustSize();
}

void SimpleButtonWidget::parseXml(const RobotGui::WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {

}

void SimpleButtonWidget::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::ID_ATR, configInfo->id.c_str()));
}
