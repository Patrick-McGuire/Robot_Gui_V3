//
// Created by nathan on 12/30/21.
//

#include "BasicImageDisplay.h"

#include <utility>

BasicImageDisplay::BasicImageDisplay(QImage _image, int _targetWidth, QWidget *parent) : QLabel(parent) {
    image = std::move(_image);
    targetWidth = _targetWidth;

    setTargetWidth(_targetWidth);
}

void BasicImageDisplay::setTargetWidth(int _targetWidth) {
    auto temp_image = image.scaledToWidth(_targetWidth);

    setGeometry(0, 0, temp_image.width(), temp_image.height());
    setPixmap(QPixmap::fromImage(temp_image));
}

