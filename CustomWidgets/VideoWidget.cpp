//
// Created by patrick on 10/17/21.
//

#include "VideoWidget.h"

VideoWidget::VideoWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData)  {
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
        // Set the size of the widget
//        if(autoWidth && autoHeight) {
            std::cout << rgb_image.cols << " : " << rgb_image.rows << "\n";
//            videoWidget.setFixedSize(rgb_image.cols, rgb_image.rows);
//            std::cout << videoWidget.height() << " : " << videoWidget.width() << "\n";
//
//        } else if(autoWidth) {
//            videoWidget.setFixedWidth((_configInfo->height * (rgb_image.rows / rgb_image.cols)));
//        } else if(autoHeight) {
//            videoWidget.setFixedHeight((_configInfo->width * (rgb_image.cols / rgb_image.rows)));
//        }
        videoWidget.setPixmap(QPixmap::fromImage(QImage((unsigned char *) rgb_image.data, rgb_image.cols, rgb_image.rows, QImage::Format_RGB888)).scaled(_configInfo->width, _configInfo->height, Qt::KeepAspectRatio));
    }
}

