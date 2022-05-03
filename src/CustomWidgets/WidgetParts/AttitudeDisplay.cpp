//
// Created by nathan on 5/2/22.
//

#include <QtGui/QPainter>

#include "../../../lib/CommonFunctions.h"

#include "AttitudeDisplay.h"


RobotGui::AttitudeDisplay::AttitudeDisplay(WidgetData *widgetData, QWidget *parent) : QLabel(parent) {
    auto crosshairImage = widgetData->getImageAsQImage(RobotGui::CROSS_HAIR_ASSET_NAME);
    auto rollIndicatorImage = widgetData->getImageAsQImage(RobotGui::ROLL_DIAL_ASSET_NAME);
    auto rollPointerImage = widgetData->getImageAsQImage(RobotGui::ROLL_POINTER_ASSET_NAME);

    if (parentWidget() != nullptr) {
        setObjectName(parentWidget()->objectName() + "_attitude_display");
    }

    rollPointerImageDisplay = new BasicImageDisplay(rollPointerImage, 300, 300, this);
    crosshairImageDisplay = new BasicImageDisplay(crosshairImage, 300, 300, this);
    rollIndicatorImageDisplay = new BasicImageDisplay(rollIndicatorImage, 300, 300, this);

    setSize(200);
    refreshMask();
}

void RobotGui::AttitudeDisplay::setSize(int _size) {
    size = _size;

    int crosshairSize = size * 0.7;
    int indicatorSize = size * 0.9;
    int pointerSize = size * 0.07;

    setMinimumSize(size, size);
    setMaximumSize(size, size);
    crosshairImageDisplay->setTargetDimensions(crosshairSize, crosshairSize);
    rollIndicatorImageDisplay->setTargetDimensions(indicatorSize, indicatorSize);
    rollPointerImageDisplay->setTargetDimensions(pointerSize, pointerSize, 0, 50, true, false);
    adjustSize();
}

void RobotGui::AttitudeDisplay::setRollPitch(double _roll, double _pitch) {
    if (_pitch > 180) {
        _pitch -= 360;
    }

    roll = _roll;
    pitch = _pitch;
}

void RobotGui::AttitudeDisplay::refreshMask() {
    // Set up octagonal mask for painter

    int corner_size = int(width() / 8);

    QVector<QPoint> points{QPoint(corner_size, 0),
                           QPoint(0, corner_size),
                           QPoint(0, height() - corner_size),
                           QPoint(corner_size, height()),
                           QPoint(width() - corner_size, height()),
                           QPoint(width(), height() - corner_size),
                           QPoint(height(), corner_size),
                           QPoint(height() - corner_size, 0)
    };

    QPolygon poly(points);
    QRegion region(poly);
    setMask(region);
}

void RobotGui::AttitudeDisplay::paintEvent(QPaintEvent *) {
    // Horizon green rectangle
    int r = size * 2; // Rectangle width
    int r2 = size * 2;  // Rectangle height

    QPainter painter(this);  // Blue background
    painter.setPen(QPen(QColor(30, 144, 255), 0, Qt::SolidLine));
    painter.setBrush(QBrush(QColor(30, 144, 255), Qt::SolidPattern));
    painter.drawRect(0, 0, width(), height());

    painter.setPen(QPen(QColor(166, 99, 0), 0, Qt::SolidLine));  // Brown horizon
    painter.setBrush(QBrush(QColor(166, 99, 0), Qt::SolidPattern));

    int center_x = int(width() / 2);
    int center_y = int(height() / 2);
    double pitch_scale_factor = (-1.0 / 50.0) * (height() / 2.0);

    painter.translate(center_x, center_y);//Set our coordinate system to be centered on the widget
    painter.rotate(-roll);

    painter.drawRect(-r, pitch_scale_factor * pitch, 2 * r, r2);

    //Pitch marker
    int line_width = int(width() / 200);
    int font_size = fmax(int(width() / 30.0), 8);
    int short_length = width() / 8.0;
    int long_length = width() / 4.0;

    painter.setPen(QPen(Qt::white, line_width, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));

    int spacing = 5; //Draw lines every 5 degrees
    int nearest_pitch = spacing * round(pitch / spacing);
    int max_to_draw_line = int(abs((width() * 0.5) / (2 * pitch_scale_factor))); // Figure out the biggest pitch to get a line drawn
    double max_pitch = fmin(nearest_pitch + max_to_draw_line + spacing, 91);
    double min_pitch = fmax(nearest_pitch - max_to_draw_line, -90);

    for (double i = min_pitch; i <= max_pitch; i += spacing) {
        double nearest_pitch_delta = (pitch - i) * pitch_scale_factor;

        int text_distance = 0;

        if (int(i) % 10 != 0) {
            painter.drawLine(-short_length / 2, nearest_pitch_delta, short_length / 2, nearest_pitch_delta);
            text_distance = short_length / 2;
        } else {
            painter.drawLine(-long_length / 2, nearest_pitch_delta, long_length / 2, nearest_pitch_delta);
            text_distance = long_length / 2;
        }

        painter.setFont(QFont("Helvetica", font_size));
        painter.drawText(text_distance * 1.1, nearest_pitch_delta + int(font_size / 2), QString::fromStdString(CommonFunctions::RoundToString(i, 0)));
        painter.drawText(-(text_distance * 1.1 + (font_size - 2) * 2), nearest_pitch_delta + int(font_size / 2), QString::fromStdString(CommonFunctions::RoundToString(i, 0)));
    }

    rollIndicatorImageDisplay->setRotation(-roll);
}


