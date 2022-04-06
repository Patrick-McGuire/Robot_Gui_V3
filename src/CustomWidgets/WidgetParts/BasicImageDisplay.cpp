//
// Created by nathan on 12/30/21.
//

#include "BasicImageDisplay.h"

#include <utility>

RobotGui::BasicImageDisplay::BasicImageDisplay(QImage _image, int _targetWidth, int _targetHeight, QWidget *parent) : QLabel(parent) {
    image = std::move(_image);
    setTargetDimensions(_targetWidth, _targetHeight);
}

void RobotGui::BasicImageDisplay::setTargetDimensions(int _targetWidth, int _targetHeight) {
    targetWidth = _targetWidth;
    targetHeight = _targetHeight;

    resizedImage = image.scaledToWidth(targetWidth);
    setGeometry(0, 0, resizedImage.width(), resizedImage.height());

    drawImage();
}

void RobotGui::BasicImageDisplay::setRotation(double _rotation) {
    rotation = _rotation;
    drawImage();
}

void RobotGui::BasicImageDisplay::drawImage() {
    QImage rotatedImage = resizedImage.transformed(QTransform().rotate(rotation));

    int widthOffset = (rotatedImage.width() - targetWidth) / 2;
    int heightOffset = (rotatedImage.height() - targetHeight) / 2;
    setGeometry(-widthOffset, -heightOffset, rotatedImage.width(), rotatedImage.height());

    setPixmap(QPixmap::fromImage(rotatedImage));
}

