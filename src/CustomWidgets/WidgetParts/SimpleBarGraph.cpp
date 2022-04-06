//
// Created by nathan on 12/25/21.
//

#include "SimpleBarGraph.h"

#include <utility>
#include <QtGui/QPainter>
#include "../../../lib/CommonFunctions.h"

SimpleBarGraph::SimpleBarGraph(QWidget *parent, std::string _title, double _min_value, double _max_value, int _size, const std::string &bar_color) : BaseGraphDisplay(parent) {
    size = _size;
    minValue = _min_value;
    maxValue = _max_value;
    title = std::move(_title);
    setSize(_size);

    if (bar_color.empty()) {
        barColor = QColor(50, 50, 255);
    } else {
        auto r_g_b = CommonFunctions::GetRGBFromString(bar_color, {50, 50, 255});
        barColor = QColor(r_g_b[0], r_g_b[1], r_g_b[2]);
    }

    textColor = QColor(255, 255, 255);

    setAlignment(Qt::AlignCenter);
}

void SimpleBarGraph::setSize(int _size) {
    size = _size;
    int width = size / 3;

    setGeometry(0, 0, width, size);
    setMinimumWidth(width);
    setMinimumHeight(size);
}

void SimpleBarGraph::paintEvent(QPaintEvent *_event) {
    QPainter painter(this);

    int fontSize = int(fmax(int(width() * 0.15), 8));
    int padding = 4;
    painter.setPen(QPen(textColor, 1, Qt::SolidLine));
    painter.setFont(QFont("Monospace", fontSize));
    int fontHeight = int(fontSize * 1.5);

    std::string valueText = CommonFunctions::RoundToString(dataValue, 2);

    painter.drawText(QRect(0, padding, width(), fontHeight), Qt::AlignCenter, tr(title.c_str()));
    painter.drawText(QRect(0, height() - fontHeight - padding, width(), fontHeight), Qt::AlignCenter, tr(valueText.c_str()));

    painter.setPen(QPen(QColor(100, 100, 100), 0, Qt::SolidLine));
    painter.setBrush(QBrush(QColor(50, 50, 50), Qt::SolidPattern));

    int topY = 2 * padding + fontHeight;
    int rectangleHeight = height() - 2 * topY;
    int startX = int(width() * 0.1);
    int rectangleWidth = width() - 2 * startX;

    painter.translate(0, topY + rectangleHeight);
    painter.drawRect(startX, 0, rectangleWidth, -rectangleHeight);
    painter.setPen(QPen(barColor, 0, Qt::SolidLine));
    painter.setBrush(QBrush(barColor, Qt::SolidPattern));

    int barHeight = int(CommonFunctions::Clamp(CommonFunctions::Interpolate(dataValue, minValue, maxValue, 0, rectangleHeight), 0, rectangleHeight));
    painter.drawRect(startX, 0, rectangleWidth, -barHeight);
}

