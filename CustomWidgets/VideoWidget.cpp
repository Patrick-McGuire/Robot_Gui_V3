//
// Created by patrick on 10/17/21.
//

#include "VideoWidget.h"

VideoWidget::VideoWidget(QWidget *parent, WidgetInfo *configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData)  {
    this->setLayout(&layout);
    layout.addWidget(&videoWidget);
//    videoWidget.setFixedHeight(480);
    videoWidget.setFixedSize(480, 320);
//    pixels = new QPixmap(480, 320);
//    pixels = pixels.scaled(100, 100, Qt::KeepAspectRatio);
//    pixels->fill(Qt::red);

//    QPixmap image(480,320);
//    image.fill(Qt::red);
//    videoWidget.setPixmap(image);
}

void VideoWidget::updateData() {
//    std::cout << "sf\n";
//    QPixmap pixels(480, 320);
//    pixels.fill(Qt::red);
//    videoWidget.setPixmap(pixels);
//    if()
//    cv::imshow("HIF", _widgetData->getImg("1"));
//    if (cv::waitKey(10) == 27) {}
    videoWidget.setPixmap(QPixmap::fromImage(QImage((unsigned char*) _widgetData->getImg("1").data, _widgetData->getImg("1").cols, _widgetData->getImg("1").rows, QImage::Format_RGB888)));
}
