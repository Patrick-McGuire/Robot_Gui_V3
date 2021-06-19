#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H
#include <QObject>
#include <QTimer>
#include "WidgetData.h"
#include "CustomWidgets/TextBoxWidget.h"

class RobotGUI : public QObject {
Q_OBJECT
public:
    QTimer *timer;
    RobotGUI(QWidget *parent, WidgetData *widgetData, TextBoxWidget *textBoxWidget);

public slots:
    void updateGUI();

private:
    WidgetData *_widgetData;
    int count;
    double count2;
    TextBoxWidget *_textBoxWidget;
};


#endif //ROBOT_GUI_V3_ROBOTGUI_H
