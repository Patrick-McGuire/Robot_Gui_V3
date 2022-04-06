#include "SimpleButtonWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"

SimpleButtonWidget::SimpleButtonWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    styledText = true;
    styledWidgetBackgroundColor = true;
    drawBorder = false;
    configurablePos = true;

    button = new QPushButton(QString::fromStdString(configInfo->title), this);
    button->adjustSize();
    adjustSize();
    setFixedSize(width() + 5, height() + 5);            // So you can drag
    button->setObjectName(this->objectName() + BUTTON_WIDGET_NAME);

    connect(button, SIGNAL(pressed()), this, SLOT(onClick()));
    connect(button, SIGNAL(released()), this, SLOT(onRelease()));
}

void SimpleButtonWidget::onClick() {
    widgetData->raiseOutputFlag(configInfo->id);
    auto json = widgetData->getOutputJson()->mapGetOrAdd(configInfo->id);
    json->setBool(true);
}

void SimpleButtonWidget::onRelease() {
    auto json = widgetData->getOutputJson()->mapGetOrAdd(configInfo->id);
    json->setBool(false);
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
