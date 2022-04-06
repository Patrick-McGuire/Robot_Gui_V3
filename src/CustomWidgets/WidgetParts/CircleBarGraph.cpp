//
// Created by nathan on 12/25/21.
//

#include <QtGui/QPainter>
#include "CircleBarGraph.h"
#include "../../../lib/CommonFunctions.h"

CircleBarGraph::CircleBarGraph(QWidget *parent, std::string _title, double _min_value, double _max_value, int _size, const std::string &bar_color) : BaseGraphDisplay(parent) {
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

void CircleBarGraph::setSize(int _size) {
    size = _size;

    setGeometry(0, 0, size, size);
    setMinimumWidth(size);
    setMinimumHeight(size);
}

void CircleBarGraph::paintEvent(QPaintEvent *_event) {
    QPainter painter(this);

    int fontSize = int(width() * 0.1);
    int padding = 4;
    painter.setPen(QPen(textColor, 1, Qt::SolidLine));
    painter.setFont(QFont("Monospace", fontSize));
    int fontHeight = int(fontSize * 1.5);

    std::string valueText = CommonFunctions::RoundToString(dataValue, 2);
    painter.drawText(QRect(0, 0, width(), height() * 0.9), Qt::AlignCenter, tr(valueText.c_str()));

    painter.setFont(QFont("Monospace", fontSize / 2));
    painter.drawText(QRect(0, (height() * 0.9 / 2) + fontHeight / 2 + padding, width(), fontHeight / 2), Qt::AlignCenter, tr(title.c_str()));

    double theta = CommonFunctions::Clamp(CommonFunctions::Interpolate(dataValue, minValue, maxValue, 0, 360 * 16), 0, 360 * 16);
    int barPadding = 20;

    painter.setPen(QPen(barColor, 30, Qt::SolidLine));
    painter.translate(0, height());
    painter.rotate(-90);

    painter.drawArc(barPadding, barPadding, width() - 2 * barPadding, height() - 2 * barPadding, 0, -theta);
}
