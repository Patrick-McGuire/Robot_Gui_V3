//
// Created by patrick on 10/17/21.
//
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include <string>
#include "../WidgetData.h"
#include "BaseWidget.h"
#include <QImage>

#ifndef ROBOT_GUI_V3_VIDEOWIDGET_H
#define ROBOT_GUI_V3_VIDEOWIDGET_H


class VideoWidget : public BaseWidget {
private:
    QLabel videoWidget;
    QGridLayout layout;


public:
    /**
     * Constructor
     * @param name  name of widget
     * @param x     x position of the widget
     * @param y     y position of the widget
     */
    VideoWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData);

    static void parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);

    void updateInFocus() override;
    void updateNoFocus() override;
    void updateOnInFocus() override;
    void customUpdate() override;
};

//typedef std::shared_ptr<VideoWidget> VideoWidget_ptr;
#endif //ROBOT_GUI_V3_VIDEOWIDGET_H
