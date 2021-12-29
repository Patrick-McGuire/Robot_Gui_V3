//
// Created by nathan on 12/29/21.
//

#include "LineTextDisplay.h"

#include <utility>
#include <iostream>
#include <cmath>

#include "../../CommonFunctions.h"

LineTextDisplay::LineTextDisplay(QWidget *parent) : QLabel(parent) {
    setFont(QFont("Monospace", 12));
}

void LineTextDisplay::setLine(int index, std::string first, std::string second) {
    if (index < lines.size()) {
        lines[index][0] = std::move(first);
        lines[index][1] = std::move(second);
    } else {
        lines.push_back({first, second});
    }
}

void LineTextDisplay::clearLinesAfterIndex(int index) {
    lines.erase(lines.begin() + index, lines.end());
}

void LineTextDisplay::updateDisplayString() {
    int maxLength = 0;
    for (auto &line : lines) {
        int lineLength = int(line[0].length());
        maxLength = int(fmax(maxLength, lineLength));
    }

    std::string outString;
    for (auto &line: lines) {
        std::string spaces = ":";

        for (int i = 0; i < maxLength - line[0].length() + 2; i++) {
            spaces += " ";
        }

        std::string newLine = line[0] + spaces + line[1] + "\n";
        outString += newLine;
    }
    outString = CommonFunctions::Strip(outString);

    setText(QString::fromStdString(outString));
    adjustSize();
}

