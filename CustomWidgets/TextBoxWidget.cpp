#include "TextBoxWidget.h"
#include <QString>
#include <iostream>
#include <vector>

TextBoxWidget::TextBoxWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    styledHeader = true;
    styledText = true;
    styledSeeThroughBackground = true;
    styledWidgetBackgroundColor = true;

    layout = new QGridLayout();
    titleBox = new QLabel();
    textBox = new QLabel();
    titleBox->setObjectName(this->objectName() + textBoxTittleBoxName);
    textBox->setObjectName(this->objectName() + textBoxTextBoxName);
    layout->addWidget(titleBox);
    layout->addWidget(textBox);
    this->setLayout(layout);

    titleBox->setText(QString::fromStdString(configInfo->title));
    textBox->setText(QString::fromStdString(GetInfoString()));

    layout->setMargin(0);
    titleBox->setMargin(0);
    textBox->setMargin(0);
    this->setAttribute(Qt::WA_StyledBackground, true);                                  // QWidget don't have this enabled by default, but most QWidgets do

    for(auto it = _configInfo->lines.begin(); it != _configInfo->lines.end(); ++it) {
        lineKeys.push_back(it[0][1]);
    }
}

std::string TextBoxWidget::GetInfoString() {
    std::string output;
    for(auto it = _configInfo->lines.begin(); it != _configInfo->lines.end(); ++it) {
        output += it[0][0];
        output += ": ";
        WidgetData::internalJsonTypes keyType = _widgetData->getKeyType(it[0][1]); //&it[0][0][1]
        if (keyType == WidgetData::int_t) {
            output += std::to_string(_widgetData->getInt(it[0][1]));
        } else if (keyType == WidgetData::double_t) {
            output += std::to_string(_widgetData->getDouble(it[0][1]));
        } else if (keyType == WidgetData::string_t) {
            output += _widgetData->getString(it[0][1]);
        } else if(keyType == WidgetData::bool_t) {
            output += _widgetData->getBool(it[0][1]) ? "True" : "False";
        } else {
            output += "err";
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
    this->adjustSize();
}

void TextBoxWidget::customUpdateStyle(bool overwrite) {
    std::string tittleTextColor = _configInfo->headerColor;
    std::string textColor = _configInfo->textColor;
    std::string backgroundColor = _configInfo->backgroundColor;
    if(overwrite || _configInfo->textColor == xmlThemeConst) {
        textColor = Theme::getTextColorStr(currentTheme);
    }
    if(overwrite || _configInfo->headerColor == xmlThemeConst) {
        tittleTextColor = Theme::getHeaderTextColorStr(currentTheme);
    }
    if(overwrite || _configInfo->backgroundColor == xmlThemeConst) {
        if(_configInfo->backgroundColor != xmlNoneConst) {
            backgroundColor = Theme::getWidgetBackgroundColorStr(currentTheme);
        } else {
            backgroundColor = "transparent";
        }
    } else if(_configInfo->backgroundColor == xmlNoneConst) {
        backgroundColor = "transparent";
    }

    char buf[400];
    sprintf(buf, "QWidget#%s{ background: %s } QWidget#%s{ background: %s; color: %s } QWidget#%s{ background: %s; color: %s }",
            this->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            titleBox->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            tittleTextColor.c_str(),
            textBox->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            textColor.c_str()
            );
    this->setStyleSheet(buf);
}

