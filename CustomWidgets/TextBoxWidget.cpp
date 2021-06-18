#include "TextBoxWidget.h"
#include <QString>
#include <iostream>
#include "../WidgetInfo.h"
#include <vector>

TextBoxWidget::TextBoxWidget(QWidget *parent, WidgetInfo *configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    this->setLayout(&layout);
    layout.addWidget(&titleBox);
    layout.addWidget(&textBox);

    titleBox.setText(QString::fromStdString(*_name));
    textBox.setText(QString::fromStdString(GetInfoString()));
}

std::string TextBoxWidget::GetInfoString() {
    std::string output;
    for(auto it = _configInfo->lines.begin(); it != _configInfo->lines.end(); ++it) {
        output += it[0][0];
        output += ": ";
        output += std::to_string(_widgetData->getInt(it[0][1]));
        output += "\n";
    }
    return output;
}

void TextBoxWidget::updateData() {
    textBox.setText(QString::fromStdString(GetInfoString()));
//    std::cout << _widgetData->getInt("KEY1");
//    std::cout << "\n";
}
