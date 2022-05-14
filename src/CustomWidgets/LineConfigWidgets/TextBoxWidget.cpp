#include "TextBoxWidget.h"
#include "../../WidgetData.h"
#include "../../InternalJson.h"
#include "../../Theme.h"
#include "../BaseStructure/BaseWidget.h"
#include <QString>
#include <iostream>
#include <vector>

RobotGui::TextBoxWidget::TextBoxWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    styledHeader = true;
    styledText = true;
    styledSeeThroughBackground = true;
    styledWidgetBackgroundColor = true;
    configurablePos = true;

    if(configInfo->type == RobotGui::WidgetConstants::TEXT_BOX) {
        lineConfig = std::dynamic_pointer_cast<LineConfig> (configInfo);
    } else {
        lineConfig = LineConfig::create();
    }

    layout = new QGridLayout();
    titleBox = new QLabel();
    textBox = new LineTextDisplay();
    titleBox->setObjectName(this->objectName() + textBoxTittleBoxName);
    textBox->setObjectName(this->objectName() + textBoxTextBoxName);
    layout->addWidget(titleBox);
    layout->addWidget(textBox);
    this->setLayout(layout);

    titleBox->setText(configInfo->title.is_initialized() ? configInfo->title->c_str() : "err");
    titleBox->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    layout->setMargin(5);
    titleBox->setMargin(0);
    this->setAttribute(Qt::WA_StyledBackground, true);                                  // QWidget don't have this enabled by default, but most QWidgets do

    titleBox->setFont(QFont(font()));
    textBox->setFont(QFont("monospace", font().pointSize()));
    customUpdate();
}

void RobotGui::TextBoxWidget::customUpdateFromConfigInfo() {
    if(configInfo->title.is_initialized()) {
        titleBox->setText(configInfo->title->c_str());
    }
}

void RobotGui::TextBoxWidget::updateInFocus() {
    if(lineConfig->lines.empty()) {
        textBox->clearLinesAfterIndex(0);
        textBox->updateDisplayString();
        return;
    }
    for (auto &line : lineConfig->lines) {
        if (widgetData->keyUpdated(line.source)) {
            customUpdate();
            return;
        }
    }
}

void RobotGui::TextBoxWidget::updateNoFocus() {

}

void RobotGui::TextBoxWidget::updateOnInFocus() {
    customUpdate();
}

void RobotGui::TextBoxWidget::customUpdate() {
    int i = 0;

    for (auto &line : lineConfig->lines) {
        std::string val;
        RobotGui::InternalJson::SharedPtr jsonVal = widgetData->getJson()->mapGet(line.source);

        if (jsonVal->getType() == RobotGui::InternalJson::int_t) {
            val += std::to_string(jsonVal->getInt());
        } else if (jsonVal->getType() == RobotGui::InternalJson::double_t) {
            val += std::to_string(jsonVal->getDouble());
        } else if (jsonVal->getType() == RobotGui::InternalJson::string_t) {
            val += jsonVal->getString();
        } else if (jsonVal->getType() == RobotGui::InternalJson::bool_t) {
            val += jsonVal->getBool() ? "True" : "False";
        } else {
            val += "No Data";
        }

        textBox->setLine(i, line.label, val);
        i++;
    }

    textBox->clearLinesAfterIndex(lineConfig->lines.size());
    textBox->updateDisplayString();
    this->adjustSize();
}

void RobotGui::TextBoxWidget::customUpdateStyle() {
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


