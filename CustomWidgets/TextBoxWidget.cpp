#include "TextBoxWidget.h"
#include <QString>
#include <iostream>
#include "../WidgetInfo.h"
#include <vector>
#include "../Constants.h"

TextBoxWidget::TextBoxWidget(QWidget *parent, WidgetInfo *configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    this->setLayout(&layout);
    layout.addWidget(&titleBox);
    layout.addWidget(&textBox);

    titleBox.setText(QString::fromStdString(*_name));
    textBox.setText(QString::fromStdString(GetInfoString()));
    textBox.setFixedWidth(500);
}

std::string TextBoxWidget::GetInfoString() {
    std::string output;
    for(auto it = _configInfo->lines.begin(); it != _configInfo->lines.end(); ++it) {
        output += it[0][0];
        output += ": ";
        std::string keyType = _widgetData->getKeyType(it[0][1]);
        if(keyType == intType) {
            output += std::to_string(_widgetData->getInt(it[0][1]));
        } else if(keyType == doubleType) {
            output += std::to_string(_widgetData->getDouble(it[0][1]));
        } else if(keyType == stringType) {
            output += _widgetData->getString(it[0][1]);
        } else {
            output += "Invalid Key or datatype";
        }
        output += "\n";

    }
    return output;
}

void TextBoxWidget::updateData() {
    textBox.setText(QString::fromStdString(GetInfoString()));
}
