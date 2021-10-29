//
// Created by patrick on 10/17/21.
//

#include "VideoWidget.h"

VideoWidget::VideoWidget(QWidget *parent, WidgetInfo *configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData)  {
    this->setLayout(&layout);
    layout.addWidget(&videoWidget);
    videoWidget.setFixedSize(480, 320);
}

void VideoWidget::updateData() {
    if(_widgetData->imgExits(_configInfo->videoId)) {
        cv::Mat rgb_image;
        cv::cvtColor(_widgetData->getImg(_configInfo->videoId), rgb_image, cv::COLOR_BGR2RGB);
        videoWidget.setPixmap(QPixmap::fromImage(QImage((unsigned char *) rgb_image.data, rgb_image.cols, rgb_image.rows, QImage::Format_RGB888)));
    }
}

