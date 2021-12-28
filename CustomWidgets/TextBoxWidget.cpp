#include "TextBoxWidget.h"
#include <QString>
#include <iostream>
#include <vector>

TextBoxWidget::TextBoxWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr& configInfo, WidgetData *widgetData, Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    styledHeader = true;
    styledText = true;
    styledSeeThroughBackground = true;
    styledWidgetBackgroundColor = true;
    configurablePos = true;

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

    for(auto it = configInfo->lines.begin(); it != configInfo->lines.end(); ++it) {
        lineKeys.push_back(it[0][1]);
    }
}

std::string TextBoxWidget::GetInfoString() {
    std::string output;
    for(auto it = configInfo->lines.begin(); it != configInfo->lines.end(); ++it) {
        output += it[0][0];
        output += ": ";
        WidgetData::internalJsonTypes keyType = widgetData->getKeyType(it[0][1]); //&it[0][0][1]
        if (keyType == WidgetData::int_t) {
            output += std::to_string(widgetData->getInt(it[0][1]));
        } else if (keyType == WidgetData::double_t) {
            output += std::to_string(widgetData->getDouble(it[0][1]));
        } else if (keyType == WidgetData::string_t) {
            output += widgetData->getString(it[0][1]);
        } else if(keyType == WidgetData::bool_t) {
            output += widgetData->getBool(it[0][1]) ? "True" : "False";
        } else {
            output += "err";
        }
        output += "\n";

    }
    output.pop_back();
    return output;
}

void TextBoxWidget::updateInFocus() {
    for(auto & lineKey : lineKeys) {
        if(widgetData->keyUpdated(lineKey)) {
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

void TextBoxWidget::customUpdateStyle() {
    char buf[400];
    sprintf(buf, "QWidget#%s{ background: %s } QWidget#%s{ background: %s; color: %s } QWidget#%s{ background: %s; color: %s }",
            this->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            titleBox->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            titleTextColor.c_str(),
            textBox->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            bodyTextColor.c_str()
            );
    this->setStyleSheet(buf);
}

void TextBoxWidget::parseXml(const RobotGui::WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node) {
    // Iterate though all lines
    for(auto *line = node->first_node(); line; line = line->next_sibling()) {
        std::string tagName = line->name();
        if(tagName == RobotGui::Xml::LINE_TAG) {
            std::string label;
            std::string value;
            for(rapidxml::xml_attribute<> *attr = line->first_attribute(); attr; attr = attr->next_attribute()) {
                std::string attrName = attr->name();
                std::string attrVal = attr->value();
                if(attrName == RobotGui::Xml::LABEL_ATR) {
                    label = attrVal;
                } else if(attrName == RobotGui::Xml::VALUE_ATR) {
                    value = attrVal;
                }
            }
            parentConfig->lines.emplace_back(std::vector<std::string> {label, value});
        }
    }
}

void TextBoxWidget::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {
    for(auto & lineConfig : configInfo->lines) {
        rapidxml::xml_node<> *line = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::LINE_TAG);
        node->append_node(line);
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::LABEL_ATR, lineConfig[0].c_str()));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::VALUE_ATR, lineConfig[1].c_str()));
    }
}

