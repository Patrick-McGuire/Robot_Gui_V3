//
// Created by patrick on 10/17/21.
//

#include "VideoWidget.h"

VideoWidget::VideoWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData)  {
    styledBackground = false;
    styledHeader = false;
    styledText = false;
    styledSeeThroughBackground = false;


    this->setLayout(&layout);
    layout.addWidget(&videoWidget);
    autoHeight = configInfo->height == xmlAutoConstID;
    autoWidth = configInfo->width == xmlAutoConstID;
    if(!autoHeight) { videoWidget.setFixedHeight(configInfo->height); }
    if(!autoWidth) { videoWidget.setFixedWidth(configInfo->width); }
}

void VideoWidget::parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node) {

}

void VideoWidget::updateInFocus() {
    if(_widgetData->keyUpdated(_configInfo->id)) {
        customUpdate();
    }
}

void VideoWidget::updateNoFocus() {

}

void VideoWidget::updateOnInFocus() {
    customUpdate();
}

void VideoWidget::customUpdate() {
    if(_widgetData->imgExits(_configInfo->id)) {
        cv::Mat rgb_image;
        cv::cvtColor(_widgetData->getImg(_configInfo->id), rgb_image, cv::COLOR_BGR2RGB);
        videoWidget.setPixmap(QPixmap::fromImage(QImage((unsigned char *) rgb_image.data, rgb_image.cols, rgb_image.rows, QImage::Format_RGB888)).scaled(_configInfo->width, _configInfo->height, Qt::KeepAspectRatio));
    }
}

