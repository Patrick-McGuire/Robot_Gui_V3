#ifndef ROBOT_GUI_V3_TEXTBOXWIDGET_H
#define ROBOT_GUI_V3_TEXTBOXWIDGET_H
#include "BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include "../WidgetInfo.h"
#include <string>
#include "../WidgetData.h"

class TextBoxWidget: public BaseWidget  {
private:
    QLabel textBox;
    QLabel titleBox;
    QGridLayout layout;

    std::string GetInfoString();
public:
    /**
     * Constructor
     * @param name  name of widget
     * @param x     x position of the widget
     * @param y     y position of the widget
     */
    TextBoxWidget(QWidget *parent, WidgetInfo *configInfo, WidgetData *widgetData);
    void updateData();
};

#endif //ROBOT_GUI_V3_TEXTBOXWIDGET_H
