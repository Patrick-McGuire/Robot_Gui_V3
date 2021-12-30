//
// Created by nathan on 12/30/21.
//

#include "CompassDisplay.h"

#include "../../RobotGui.h"

CompassDisplay::CompassDisplay(WidgetData *widgetData, QWidget *parent) : QLabel(parent) {
    auto backgroundImage = widgetData->getImageAsQImage(RobotGui::COMPASS_ASSET_NAME);

    backgroundImageWidget = new BasicImageDisplay(backgroundImage, 300, this);
    setSize(300);
}

void CompassDisplay::setSize(int size) {
    setMinimumSize(size, size);
    setMaximumSize(size, size);
    backgroundImageWidget->setTargetWidth(size);
    adjustSize();
}
