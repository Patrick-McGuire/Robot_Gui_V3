//
// Created by nathan on 12/28/21.
//

#include "MissionStatusWidget.h"

#include <QLabel>
#include <QGridLayout>
#include <QSizePolicy>

#include "../CommonFunctions.h"
#include "../WidgetData.h"

MissionStatusWidget::MissionStatusWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, RobotGui::WidgetData *widgetData, Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    statusBox = new QLabel();
    missionNameBox = new QLabel();
    objectiveBox = new QLabel();

    auto layout = new QGridLayout();
    layout->addWidget(statusBox, 1, 1, 1, 2);
    layout->addWidget(missionNameBox, 2, 1, 1, 1);
    layout->addWidget(objectiveBox, 2, 2, 1, 1);
    setLayout(layout);

    statusSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "statusSource", "missionStatus");
    missionNameSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "missionNameSource", "missionName");
    objectiveSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "objectiveNameSource", "objectiveName");
    size = configInfo->size;
    if (size == 0) { size = 30; }

    statusBox->setFont(QFont("Monospace", size));
    statusBox->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    statusBox->setMinimumWidth(size * 8);
    statusBox->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));

    missionNameBox->setFont(QFont("Monospace", size / 3));
    missionNameBox->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    missionNameBox->setMinimumWidth(size);

    objectiveBox->setFont(QFont("Monospace", size / 3));
    objectiveBox->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    objectiveBox->setMinimumWidth(size);
}

void MissionStatusWidget::updateInFocus() {
    std::string missionStatus = widgetData->getJson()->mapGet(statusSource)->getString("Unknown");
    std::string missionName = widgetData->getJson()->mapGet(missionNameSource)->getString("Unknown");
    std::string objectiveName = widgetData->getJson()->mapGet(objectiveSource)->getString("Unknown");

    statusBox->setText(QString::fromStdString(missionStatus));
    missionNameBox->setText(QString::fromStdString("Mission: " + missionName));
    objectiveBox->setText(QString::fromStdString("Objective: " + objectiveName));

    missionNameBox->adjustSize();
    objectiveBox->adjustSize();
    adjustSize();
}

void MissionStatusWidget::customUpdateStyle() {
    statusBox->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
    missionNameBox->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
    objectiveBox->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
}
