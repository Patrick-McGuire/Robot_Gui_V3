//
// Created by nathan on 1/25/22.
//

#ifndef ROBOT_GUI_V3_SIDETABWIDGET_H
#define ROBOT_GUI_V3_SIDETABWIDGET_H

#include "QWidget"

#include "QPushButton"
#include "QStackedWidget"
#include "QGridLayout"

class SideTabWidget : public QWidget {
public:
    explicit SideTabWidget(QWidget *parent = nullptr);

    void addTab(const std::string &tabName, QWidget *tabWidget);

    int getTabIndexFromName(const std::string& tabName);

protected:
    void buttonPressed(const std::string &buttonName);

private:
    QGridLayout *buttonLayout;
    QStackedWidget *stackedWidget;
    std::vector<QPushButton *> tabOptionsList;
    std::vector<std::string> tabNames;
};


#endif //ROBOT_GUI_V3_SIDETABWIDGET_H
