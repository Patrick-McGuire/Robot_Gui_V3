//
// Created by nathan on 12/29/21.
//

#include "DropDownTextBoxWidget.h"

#include <QComboBox>
#include <QGridLayout>

#include "WidgetParts/LineTextDisplay.h"

DropDownTextBoxWidget::DropDownTextBoxWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme) : BaseWidget(parent, configInfo, widgetData, theme) {
    textDisplay = new LineTextDisplay();
    selectionBox = new QComboBox();

    auto layout = new QGridLayout();
    layout->addWidget(selectionBox);
    layout->addWidget(textDisplay);
    setLayout(layout);

    selectionBox->addItem("No Data");
    selectionBox->setDuplicatesEnabled(false);
    selectionBox->setInsertPolicy(QComboBox::InsertAlphabetically);
    selectionBox->setFont(font());

    textDisplay->setFont(QFont("Monospace", font().pointSize()));
}

void DropDownTextBoxWidget::updateInFocus() {
    if (widgetData->keyUpdated(configInfo->source)) {
        auto pages = widgetData->getJson()->mapGet(configInfo->source);
        pages->print();
        if (pages->getType() == InternalJson::map_t) {
            std::string currentSelection = selectionBox->currentText().toStdString();

            auto keys = pages->mapKeys();
            setDropDownItems(keys);

            if (pages->mapCount(currentSelection)) {
                auto lines = pages->mapGet(currentSelection);
                if (lines->getType() == InternalJson::vector_t) {
                    for (int i = 0; i < lines->vectorSize(); i++) {
                        textDisplay->setLine(i, lines->vectorGet(i)->vectorGet(0)->getString(), lines->vectorGet(i)->vectorGet(1)->getString());
                    }
                    textDisplay->clearLinesAfterIndex(int(lines->vectorSize()));
                    textDisplay->updateDisplayString();
                }
            }
        }
    }

    adjustSize();
}

void DropDownTextBoxWidget::setDropDownItems(std::vector<std::string> keys) {
    if (selectionBox->count() != keys.size()) {
        selectionBox->clear();
        for (auto &key : keys) {
            selectionBox->addItem(QString::fromStdString(key));
        }
    }

    for (int i = 0; i < keys.size(); i++) {
        selectionBox->setItemText(i, QString::fromStdString(keys[i]));
    }
}

void DropDownTextBoxWidget::customUpdateStyle() {
    textDisplay->setStyleSheet(QString::fromStdString("color: " + bodyTextColor));
    selectionBox->setStyleSheet(QString::fromStdString("background: " + backgroundColor + "; color: " + titleTextColor));
}
