#include "ROVStatusWidget.h"
#include "../../../lib/CommonFunctions.h"
#include "../../WidgetData.h"
#include "../../Theme.h"
#include "../BaseStructure/BaseWidget.h"

#include <QLabel>
#include <QGridLayout>

RobotGui::ROVStatusWidget::ROVStatusWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *theme) : BaseWidget(parent, configInfo,
                                                                                                                                                                                 widgetData, theme) {

    if (configInfo->type == ROV_STATUS) {
        sourceMapConfig = std::dynamic_pointer_cast<SourceMapConfig>(configInfo);
    } else {
        sourceMapConfig = SourceMapConfig::create();
    }

    statusSource = CommonFunctions::GetStringFromMap(sourceMapConfig->sourceMap, "statusSource", "status");
    armedSource = CommonFunctions::GetStringFromMap(sourceMapConfig->sourceMap, "armedSource", "armed");
    allowedToArmSource = CommonFunctions::GetStringFromMap(sourceMapConfig->sourceMap, "allowedToArmSource", "allowedToArm");
    modeSource = CommonFunctions::GetStringFromMap(sourceMapConfig->sourceMap, "modeSource", "driveMode");
    runtimeSource = CommonFunctions::GetStringFromMap(sourceMapConfig->sourceMap, "runtimeSource", "runtime");
    timeSource = CommonFunctions::GetStringFromMap(sourceMapConfig->sourceMap, "timeSource", "time");
    size = configInfo->size.is_initialized() ? configInfo->size.get() : 0;
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

void RobotGui::ROVStatusWidget::updateInFocus() {
    int faultStatus = widgetData->getJson()->mapGet(statusSource)->getInt(3);
    bool canArm = widgetData->getJson()->mapGet(allowedToArmSource)->getBool(true);
    bool armed = widgetData->getJson()->mapGet(armedSource)->getBool(true);
    std::string mode = widgetData->getJson()->mapGet(modeSource)->getString("Unknown");
    std::string runTime = widgetData->getJson()->mapGet(runtimeSource)->getString("no data");
    std::string time = widgetData->getJson()->mapGet(timeSource)->getString("no data");

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

void RobotGui::ROVStatusWidget::customUpdateStyle() {
    modeBox->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
    timeBox->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
    runtimeBox->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
}
