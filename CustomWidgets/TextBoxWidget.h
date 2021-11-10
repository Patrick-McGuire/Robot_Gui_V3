#ifndef ROBOT_GUI_V3_TEXTBOXWIDGET_H
#define ROBOT_GUI_V3_TEXTBOXWIDGET_H
#include "BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include "../Configuration/WidgetInfo.h"
#include "../Configuration/ConfigStructs.h"
#include <string>
#include "../WidgetData.h"
#include "../Constants.h"
#include "../XML/XMLConstants.h"

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
    TextBoxWidget(QWidget *parent, WidgetConfig *configInfo, WidgetData *widgetData);

    static void parseXml(WidgetConfig *parentConfig, rapidxml::xml_node<> *node);

    void updateInFocus() override;
    void updateNoFocus() override;
    void updateOnInFocus() override;
};

#endif //ROBOT_GUI_V3_TEXTBOXWIDGET_H
