#ifndef ROBOT_GUI_V3_TEXTBOXWIDGET_H
#define ROBOT_GUI_V3_TEXTBOXWIDGET_H
#include "BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>

class TextBoxWidget: public BaseWidget  {
private:
    QLabel textBox;
    QLabel titleBox;
    QGridLayout layout;
public:
    /**
     * Constructor
     * @param name  name of widget
     * @param x     x position of the widget
     * @param y     y position of the widget
     */
    TextBoxWidget(QWidget *parent, std::string name, int x, int y);
//    void update();
};

#endif //ROBOT_GUI_V3_TEXTBOXWIDGET_H
