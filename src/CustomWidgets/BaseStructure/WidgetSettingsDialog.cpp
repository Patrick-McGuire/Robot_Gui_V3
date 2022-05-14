#include "WidgetSettingsDialog.h"
#include "QIntValidator"
#include "QDoubleValidator"

RobotGui::WidgetSettingsDialog::WidgetSettingsDialog() : QDialog() {
    dialogLayout = new QGridLayout;
    this->setLayout(dialogLayout);
}

QLineEdit *RobotGui::WidgetSettingsDialog::addTextEntry(const std::string &title, const std::string &text) {
    auto label = new QLabel(title.c_str());
    auto entry = new QLineEdit(text.c_str());
    dialogLayout->addWidget(label, nextRow, 0);
    dialogLayout->addWidget(entry, nextRow, 1);
    nextRow++;
    return entry;
}

QLineEdit *RobotGui::WidgetSettingsDialog::addIntEntry(const std::string &title, int val) {
    auto label = new QLabel(title.c_str());
    auto entry = new QLineEdit(std::to_string(val).c_str());
    entry->setValidator(new QIntValidator(entry) );
    dialogLayout->addWidget(label, nextRow, 0);
    dialogLayout->addWidget(entry, nextRow, 1);
    nextRow++;
    return entry;
}

QLineEdit *RobotGui::WidgetSettingsDialog::addDoubleEntry(const std::string &title, double val) {
    auto label = new QLabel(title.c_str());
    auto entry = new QLineEdit(std::to_string(val).c_str());
    entry->setValidator(new QDoubleValidator(entry) );
    dialogLayout->addWidget(label, nextRow, 0);
    dialogLayout->addWidget(entry, nextRow, 1);
    nextRow++;
    return entry;
}

QCheckBox *RobotGui::WidgetSettingsDialog::addBoolEntry(const std::string &title, bool val) {
    auto label = new QLabel("Draggable:");
    auto entry = new QCheckBox();
    dialogLayout->addWidget(label, nextRow, 0);
    dialogLayout->addWidget(entry, nextRow, 1);
    nextRow++;
    if (val) { entry->toggle(); }
    return entry;
}




