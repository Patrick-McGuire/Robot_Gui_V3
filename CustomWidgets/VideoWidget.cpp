#include "VideoWidget.h"

VideoWidget::VideoWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData)  {
    styledBackground = false;
    styledHeader = false;
    styledText = false;
    styledSeeThroughBackground = false;


    this->setLayout(&layout);
    layout.addWidget(&videoWidget);
    autoHeight = configInfo->height == XML_AUTO_CONST_ID;
    autoWidth = configInfo->width == XML_AUTO_CONST_ID;
    if(!autoHeight) { videoWidget.setFixedHeight(configInfo->height); }
    if(!autoWidth) { videoWidget.setFixedWidth(configInfo->width); }
}

void VideoWidget::parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node) {

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

