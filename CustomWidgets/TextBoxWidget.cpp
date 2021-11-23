#include "TextBoxWidget.h"
#include <QString>
#include <iostream>
#include <vector>

TextBoxWidget::TextBoxWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    wrapper = new QWidget();
    layout = new QGridLayout();
    titleBox = new QLabel();
    textBox = new QLabel();
    layout->addWidget(titleBox);
    layout->addWidget(textBox);
    wrapper->setLayout(layout);

    titleBox->setText(QString::fromStdString(configInfo->title));
    textBox->setText(QString::fromStdString(GetInfoString()));

    wrapper->setParent(this);
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
            output += "Ipe";
        }
        output += "\n";

    }
    output.pop_back();
    return output;
}

void TextBoxWidget::parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node) {
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
    textBox->setText(QString::fromStdString(GetInfoString()));
    wrapper->adjustSize();
}

void TextBoxWidget::updateTheme(Themes _theme, bool overwrite) {
    QString mainWidgetStyle = "";
    QString headerWidgetStyle = "";
    // Set the background color
    if(overwrite || _configInfo->backgroundColor == xmlThemeConst) {
        if(_configInfo->backgroundColor != xmlNoneConst) {
            mainWidgetStyle += QString("background: ") + QString::fromStdString(Theme::getBackgroundColorStr(_theme)) + ";"; //Theme::getBackgroundColorStr(_theme)
        } else {
            mainWidgetStyle += "background: transparent;";
        }
    } else if(_configInfo->backgroundColor != xmlThemeConst || _configInfo->backgroundColor != xmlNoneConst) {
        mainWidgetStyle += QString("background: ") + QString::fromStdString(_configInfo->backgroundColor) + ";";
    }
    // Set the text color
    if(overwrite || _configInfo->textColor == xmlThemeConst) {
        mainWidgetStyle += QString("color: ") + QString::fromStdString(Theme::getTextColorStr(_theme)) + ";";
        headerWidgetStyle += "color: " + QString::fromStdString(Theme::getHeaderTextColorStr(_theme)) + ";";
    } else if(_configInfo->textColor != xmlThemeConst) {
        mainWidgetStyle += QString("color: ") + QString::fromStdString(_configInfo->textColor) + ";";
    }
    this->setStyleSheet(mainWidgetStyle);
    titleBox->setStyleSheet(headerWidgetStyle);
}
