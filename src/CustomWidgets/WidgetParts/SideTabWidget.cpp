//
// Created by nathan on 1/25/22.
//

#include <iostream>
#include "SideTabWidget.h"

#include "QGridLayout"

RobotGui::SideTabWidget::SideTabWidget(QWidget *parent) : QWidget(parent) {
    stackedWidget = new QStackedWidget();

    auto main_layout = new QGridLayout();
    buttonLayout = new QGridLayout();
    main_layout->addLayout(buttonLayout, 0, 0);
    main_layout->addWidget(stackedWidget, 0, 1);
    main_layout->setMargin(1);
    setLayout(main_layout);
}

void RobotGui::SideTabWidget::addTab(const std::string &tabName, QWidget *tabWidget) {
    auto button = new QPushButton();
    button->setText(QString::fromStdString(tabName));
    connect(button, &QPushButton::clicked, [this, tabName] { buttonPressed(tabName); });

    tabOptionsList.push_back(button);
    buttonLayout->addWidget(button);
    stackedWidget->addWidget(tabWidget);
    tabNames.push_back(tabName);
}

int RobotGui::SideTabWidget::getTabIndexFromName(const std::string &tabName) {
    for (int i = 0; i < tabNames.size(); i++) {
        if (tabNames[i] == tabName) {
            return i;
        }
    }
    return -1;
}

void RobotGui::SideTabWidget::buttonPressed(const std::string &buttonName) {
    int index = getTabIndexFromName(buttonName);
    if (index != -1) {
        stackedWidget->setCurrentIndex(index);
    }
}

void RobotGui::SideTabWidget::setColorStrings(std::string background, std::string textColor, std::string border) {
    this->setStyleSheet(QString::fromStdString("color: " + textColor + "; background: " + background));

    for (auto &button : tabOptionsList) {
        button->setStyleSheet(QString::fromStdString("color: " + textColor));
    }
}


