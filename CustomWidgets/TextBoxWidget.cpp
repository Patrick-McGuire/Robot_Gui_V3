#include "TextBoxWidget.h"
#include <QString>
#include <iostream>
#include "../Configuration/WidgetInfo.h"
#include <vector>
#include "../Constants.h"

TextBoxWidget::TextBoxWidget(QWidget *parent, WidgetConfig *configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    this->setLayout(&layout);
    layout.addWidget(&titleBox);
    layout.addWidget(&textBox);

    titleBox.setText(QString::fromStdString(configInfo->title));
    textBox.setText(QString::fromStdString(GetInfoString()));
    textBox.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    for(auto it = _configInfo->lines.begin(); it != _configInfo->lines.end(); ++it) {
        lineKeys.push_back(it[0][1]);
    }
}

std::string TextBoxWidget::GetInfoString() {
    std::string output;
    for(auto it = _configInfo->lines.begin(); it != _configInfo->lines.end(); ++it) {
        output += it[0][0];
        output += ": ";
        std::string keyType = _widgetData->getKeyType(it[0][1]); //&it[0][0][1]
        if (keyType == intType) {
            output += std::to_string(_widgetData->getInt(it[0][1]));
        } else if (keyType == doubleType) {
            output += std::to_string(_widgetData->getDouble(it[0][1]));
        } else if (keyType == stringType) {
            output += _widgetData->getString(it[0][1]);
        } else if(keyType == boolType) {
            output += _widgetData->getBool(it[0][1]) ? "True" : "False";
        } else {
            output += "Invalid Key or datatype";
        }
        output += "\n";

    }
    output.pop_back();
    return output;
}

void TextBoxWidget::parseXml(struct WidgetConfig *parentConfig, rapidxml::xml_node<> *node) {
    // Iterate though all lines
    for(auto *line = node->first_node(); line; line = line->next_sibling()) {
        std::string tagName = line->name();
        if(tagName == xmlLineTag) {
            std::string label;
            std::string value;
            for(rapidxml::xml_attribute<> *attr = line->first_attribute(); attr; attr = attr->next_attribute()) {
                std::string attrName = attr->name();
                std::string attrVal = attr->value();
                if(attrName == xmlLabelATR) {
                    label = attrVal;
                } else if(attrName == xmlValueATR) {
                    value = attrVal;
                }
            }
            parentConfig->lines.emplace_back(std::vector<std::string> {label, value});
        }
    }
}

void TextBoxWidget::updateInFocus() {
    for(auto & lineKey : lineKeys) {
        if(_widgetData->keyUpdated(lineKey)) {
            customUpdate();
            return;
        }
    }
}

void TextBoxWidget::updateNoFocus() {

}

void TextBoxWidget::updateOnInFocus() {
    customUpdate();
}

void TextBoxWidget::customUpdate() {
    textBox.setText(QString::fromStdString(GetInfoString()));
}
