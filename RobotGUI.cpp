#include <QMainWindow>
#include <QApplication>
#include "RobotGUI.h"
#include <QTimer>
#include "iostream"
#include "WidgetData.h"


RobotGUI::RobotGUI(QWidget *parent, WidgetData *widgetData, TextBoxWidget *textBoxWidget) : QObject(parent) {
    _widgetData = widgetData;
    _textBoxWidget = textBoxWidget;
}

void RobotGUI::updateGUI() {
    _textBoxWidget->updateData();
}