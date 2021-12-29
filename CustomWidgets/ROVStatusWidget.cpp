//
// Created by nathan on 12/27/21.
//

#include "ROVStatusWidget.h"
#include "../CommonFunctions.h"

#include <QLabel>
#include <QGridLayout>

ROVStatusWidget::ROVStatusWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    statusSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "statusSource", "status");
    armedSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "armedSource", "armed");
    allowedToArmSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "allowedToArmSource", "allowedToArm");
    modeSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "modeSource", "driveMode");
    runtimeSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "runtimeSource", "runtime");
    timeSource = CommonFunctions::GetStringFromMap(configInfo->sourceMap, "timeSource", "time");
    size = configInfo->size;
    if (size == 0) { size = 30; } //Default value

    statusBox = new QLabel();
    armingBox = new QLabel();
    modeBox = new QLabel();
    timeBox = new QLabel();
    runtimeBox = new QLabel();

    auto *layout = new QGridLayout();
    layout->addWidget(statusBox, 1, 1, 1, 2);
    layout->addWidget(armingBox, 2, 1, 1, 2);
    layout->addWidget(modeBox, 3, 1, 1, 2);
    layout->addWidget(timeBox, 4, 1);
    layout->addWidget(runtimeBox, 4, 2);
    setLayout(layout);

    statusBox->setFont(QFont("Monospace", size));
    statusBox->setAlignment(Qt::AlignCenter);
    statusBox->setMinimumWidth(size * 8);

    armingBox->setFont(QFont("Monospace", size));
    armingBox->setAlignment(Qt::AlignCenter);
    armingBox->setMinimumWidth(size * 13);

    modeBox->setFont(QFont("Monospace", size));
    modeBox->setAlignment(Qt::AlignCenter);

    timeBox->setFont(QFont("Monospace", int(size * 0.4)));
    runtimeBox->setFont(QFont("Monospace", int(size * 0.4)));
}

void ROVStatusWidget::updateInFocus() {
    int faultStatus = widgetData->getInt(statusSource, 3);
    bool canArm = widgetData->getBool(allowedToArmSource, true);
    bool armed = widgetData->getBool(armedSource, true);
    std::string mode = widgetData->getString(modeSource, "Unknown");
    std::string runTime = widgetData->getString(runtimeSource, "no data");
    std::string time = widgetData->getString(timeSource, "no data");

    switch (faultStatus) {
        case 2:
            statusBox->setStyleSheet("color: red");
            statusBox->setText("Faulted");
            break;
        case 1:
            statusBox->setStyleSheet("color: yellow");
            statusBox->setText("Warning");
            break;
        case 0:
            statusBox->setStyleSheet("color: green");
            statusBox->setText("OK");
            break;
        default:
            statusBox->setStyleSheet("color: blue");
            statusBox->setText("Unknown");
            break;
    }

    if (!canArm) {
        armingBox->setStyleSheet("color: red");
        armingBox->setText("Arming Disabled");
    } else {
        armingBox->setStyleSheet("color: green");
        if (armed) { armingBox->setText("Armed"); }
        else { armingBox->setText("Disarmed"); }
    }

    modeBox->setText(QString::fromStdString(mode));
    timeBox->setText(QString::fromStdString("Time: " + time));
    runtimeBox->setText(QString::fromStdString("Run Time: " + runTime));

    statusBox->adjustSize();
    armingBox->adjustSize();
    modeBox->adjustSize();
    adjustSize();
}

void ROVStatusWidget::customUpdateStyle() {
    modeBox->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
    timeBox->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
    runtimeBox->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
}