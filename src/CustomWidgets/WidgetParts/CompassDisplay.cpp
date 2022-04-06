//
// Created by nathan on 12/30/21.
//

#include "CompassDisplay.h"

#include "../../RobotGui.h"
#include "../../WidgetData.h"
#include "BasicImageDisplay.h"

RobotGui::CompassDisplay::CompassDisplay(RobotGui::WidgetData *widgetData, QWidget *parent) : QLabel(parent) {
    auto backgroundImage = widgetData->getImageAsQImage(RobotGui::COMPASS_ASSET_NAME);
    auto arrowImage = widgetData->getImageAsQImage(RobotGui::ARROW_ASSET_NAME).copy(900, 900, 2100 - 900, 2100 - 900);
    auto scaledArrow = arrowImage.scaled(arrowImage.width() * 2, arrowImage.height(), Qt::AspectRatioMode::IgnoreAspectRatio);

    backgroundImageWidget = new BasicImageDisplay(backgroundImage, 300, 300, this);
    arrowImageWidget = new BasicImageDisplay(scaledArrow, 300, 300, this);
    setSize(300);
}

void RobotGui::CompassDisplay::setSize(int size) {
    setMinimumSize(size, size);
    setMaximumSize(size, size);
    backgroundImageWidget->setTargetDimensions(size, size);
    arrowImageWidget->setTargetDimensions(size, size);
    adjustSize();
}

void RobotGui::CompassDisplay::setYaw(double yaw) {
    yaw += 90;
    arrowImageWidget->setRotation(yaw);
}
