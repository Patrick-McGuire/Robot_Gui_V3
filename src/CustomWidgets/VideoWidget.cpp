#include "VideoWidget.h"
#include "../WidgetData.h"
#include "../Theme.h"
#include "BaseStructure/BaseWidget.h"

RobotGui::VideoWidget::VideoWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr& configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme)  {
    styledBackground = false;
    styledHeader = false;
    styledText = false;
    styledSeeThroughBackground = false;
    configurablePos = true;
    configurableHeight = true;
    configurableWidth = true;


    this->setLayout(&layout);
    layout.addWidget(&videoWidget);
    autoHeight = !configInfo->height.is_initialized() || (configInfo->height == RobotGui::Xml::AUTO_CONST_ID);
    autoWidth = !configInfo->width.is_initialized() || (configInfo->width == RobotGui::Xml::AUTO_CONST_ID);
    if(!autoHeight) { videoWidget.setFixedHeight(configInfo->height.get()); }
    if(!autoWidth) { videoWidget.setFixedWidth(configInfo->width.get()); }
}

void RobotGui::VideoWidget::customUpdateFromConfigInfo() {
    if(!autoHeight) { videoWidget.setFixedHeight(configInfo->height.get()); }
    if(!autoWidth) { videoWidget.setFixedWidth(configInfo->width.get()); }
    this->adjustSize();
}

void RobotGui::VideoWidget::updateInFocus() {
    if(configInfo->source.is_initialized()) {
        if (widgetData->keyUpdated(configInfo->source.get())) {
            customUpdate();
        }
    }
}

void RobotGui::VideoWidget::updateNoFocus() {

}

void RobotGui::VideoWidget::updateOnInFocus() {
    customUpdate();
}

void RobotGui::VideoWidget::customUpdate() {
    if(configInfo->source.is_initialized()) {
        if (widgetData->imgExits(configInfo->source.get())) {
            cv::Mat rgb_image;
            cv::cvtColor(widgetData->getImg(configInfo->source.get()), rgb_image, cv::COLOR_BGR2RGB);
            videoWidget.setPixmap(QPixmap::fromImage(QImage((unsigned char *) rgb_image.data, rgb_image.cols, rgb_image.rows, QImage::Format_RGB888)).scaled(configInfo->width.get(), configInfo->height.get(),
                                                                                                                                                             Qt::KeepAspectRatio));
        }
    }
}


