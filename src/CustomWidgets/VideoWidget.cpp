#include "VideoWidget.h"
#include "../WidgetData.h"

VideoWidget::VideoWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr& configInfo, RobotGui::WidgetData *widgetData, Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme)  {
    styledBackground = false;
    styledHeader = false;
    styledText = false;
    styledSeeThroughBackground = false;
    configurablePos = true;
    configurableHeight = true;
    configurableWidth = true;


    this->setLayout(&layout);
    layout.addWidget(&videoWidget);
    autoHeight = configInfo->height == RobotGui::Xml::AUTO_CONST_ID;
    autoWidth = configInfo->width == RobotGui::Xml::AUTO_CONST_ID;
    if(!autoHeight) { videoWidget.setFixedHeight(configInfo->height); }
    if(!autoWidth) { videoWidget.setFixedWidth(configInfo->width); }
}

void VideoWidget::parseXml(const RobotGui::WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node) {

}

void VideoWidget::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {
    node->append_attribute(doc->allocate_attribute(RobotGui::Xml::ID_ATR, configInfo->id.c_str()));
}

void VideoWidget::updateInFocus() {
    if(widgetData->keyUpdated(configInfo->id)) {
        customUpdate();
    }
}

void VideoWidget::updateNoFocus() {

}

void VideoWidget::updateOnInFocus() {
    customUpdate();
}

void VideoWidget::customUpdate() {
    if(widgetData->imgExits(configInfo->id)) {
        cv::Mat rgb_image;
        cv::cvtColor(widgetData->getImg(configInfo->id), rgb_image, cv::COLOR_BGR2RGB);
        videoWidget.setPixmap(QPixmap::fromImage(QImage((unsigned char *) rgb_image.data, rgb_image.cols, rgb_image.rows, QImage::Format_RGB888)).scaled(configInfo->width, configInfo->height, Qt::KeepAspectRatio));
    }
}


