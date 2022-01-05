#include "TextBoxWidget.h"
#include <QString>
#include <iostream>
#include <vector>

TextBoxWidget::TextBoxWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    styledHeader = true;
    styledText = true;
    styledSeeThroughBackground = true;
    styledWidgetBackgroundColor = true;
    configurablePos = true;

    layout = new QGridLayout();
    titleBox = new QLabel();
    textBox = new LineTextDisplay();
    titleBox->setObjectName(this->objectName() + textBoxTittleBoxName);
    textBox->setObjectName(this->objectName() + textBoxTextBoxName);
    layout->addWidget(titleBox);
    layout->addWidget(textBox);
    this->setLayout(layout);

    titleBox->setText(QString::fromStdString(configInfo->title));
    titleBox->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    layout->setMargin(5);
    titleBox->setMargin(0);
    this->setAttribute(Qt::WA_StyledBackground, true);                                  // QWidget don't have this enabled by default, but most QWidgets do

    for (auto it = configInfo->lines.begin(); it != configInfo->lines.end(); ++it) {
        lineKeys.push_back(it[0][1]);
    }

    titleBox->setFont(QFont(font()));
    textBox->setFont(QFont("monospace", font().pointSize()));
    customUpdate();
}

void TextBoxWidget::updateInFocus() {
    for (auto &lineKey : lineKeys) {
        if (widgetData->keyUpdated(lineKey)) {
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
    int i = 0;

    for (auto it = configInfo->lines.begin(); it != configInfo->lines.end(); ++it) {
        std::string first = it[0][0];
        std::string second;

        InternalJson::SharedPtr jsonVal = widgetData->getJson()->mapGet(it[0][1]);
        if (jsonVal->getType() == InternalJson::int_t) {
            second += std::to_string(jsonVal->getInt());
        } else if (jsonVal->getType() == InternalJson::double_t) {
            second += std::to_string(jsonVal->getDouble());
        } else if (jsonVal->getType() == InternalJson::string_t) {
            second += jsonVal->getString();
        } else if (jsonVal->getType() == InternalJson::bool_t) {
            second += jsonVal->getBool() ? "True" : "False";
        } else {
            second += "No Data";
        }

        textBox->setLine(i, first, second);
        i++;
    }

    textBox->updateDisplayString();
    this->adjustSize();
}

void TextBoxWidget::customUpdateStyle() {
    char buf[400];
    sprintf(buf, "QWidget#%s{ background: %s; color: %s } QWidget#%s{ background: %s; color: %s }",
            titleBox->objectName().toStdString().c_str(),
            "transparent",
            titleTextColor.c_str(),
            textBox->objectName().toStdString().c_str(),
            "transparent",
            bodyTextColor.c_str()
    );
    this->setStyleSheet(buf);

    titleBox->setFont(QFont(font()));
    textBox->setFont(QFont("monospace", font().pointSize()));
    titleBox->update();
    textBox->update();
    update();
    adjustSize();
}

void TextBoxWidget::parseXml(const RobotGui::WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node) {
    // Iterate though all lines
    for (auto *line = node->first_node(); line; line = line->next_sibling()) {
        std::string tagName = line->name();
        if (tagName == RobotGui::Xml::LINE_TAG) {
            std::string label;
            std::string value;
            for (rapidxml::xml_attribute<> *attr = line->first_attribute(); attr; attr = attr->next_attribute()) {
                std::string attrName = attr->name();
                std::string attrVal = attr->value();
                if (attrName == RobotGui::Xml::LABEL_ATR) {
                    label = attrVal;
                } else if (attrName == RobotGui::Xml::VALUE_ATR) {
                    value = attrVal;
                }
            }
            parentConfig->lines.emplace_back(std::vector < std::string > {label, value});
        }
    }
}

void TextBoxWidget::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {
    for (auto &lineConfig : configInfo->lines) {
        rapidxml::xml_node<> *line = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::LINE_TAG);
        node->append_node(line);
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::LABEL_ATR, lineConfig[0].c_str()));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::VALUE_ATR, lineConfig[1].c_str()));
    }
}

