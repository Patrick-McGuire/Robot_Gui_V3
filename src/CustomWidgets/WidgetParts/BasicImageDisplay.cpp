//
// Created by nathan on 12/30/21.
//

#include "BasicImageDisplay.h"

#include <utility>

RobotGui::BasicImageDisplay::BasicImageDisplay(QImage _image, int _targetWidth, int _targetHeight, QWidget *parent) : QLabel(parent) {
    image = std::move(_image);
    setTargetDimensions(_targetWidth, _targetHeight);
}

void RobotGui::BasicImageDisplay::setTargetDimensions(int _targetWidth, int _targetHeight, int x_offset, int y_offset, bool x_centered, bool y_centered) {
    targetWidth = _targetWidth;
    targetHeight = _targetHeight;

    xOffset = x_offset;
    yOffset = y_offset;
    xCentered = x_centered;
    yCentered = y_centered;

    resizedImage = image.scaledToWidth(targetWidth);
    drawImage();
}

void RobotGui::BasicImageDisplay::setRotation(double _rotation) {
    rotation = _rotation;
    drawImage();
}

void RobotGui::BasicImageDisplay::drawImage() {
    rotatedImage = resizedImage.transformed(QTransform().rotate(rotation));

    int x_offset = 0;
    int y_offset = 0;

    if (xCentered && this->parentWidget() != nullptr) {
        x_offset = (this->parentWidget()->width() - rotatedImage.width()) / 2;
    }

    if (yCentered && this->parentWidget() != nullptr) {
        y_offset = (this->parentWidget()->height() - rotatedImage.height()) / 2;
    }


    setGeometry(x_offset, y_offset, rotatedImage.width(), rotatedImage.height());

    setPixmap(QPixmap::fromImage(rotatedImage));
}

