#include "WidgetSettingsDialog.h"
#include "QIntValidator"
#include "QDoubleValidator"
#include "ColorEntry.h"

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
    auto label = new QLabel(title.c_str());
    auto entry = new QCheckBox();
    dialogLayout->addWidget(label, nextRow, 0);
    dialogLayout->addWidget(entry, nextRow, 1);
    nextRow++;
    if (val) { entry->toggle(); }
    return entry;
}

RobotGui::ColorEntry *RobotGui::WidgetSettingsDialog::addColorEntry(const std::string &title, const std::string &color) {
    auto label = new QLabel(title.c_str());
    auto *colorEntry = new ColorEntry();
    dialogLayout->addWidget(label, nextRow, 0);
    dialogLayout->addWidget(colorEntry, nextRow, 1);
    nextRow++;
    colorEntry->setColor(color);
    return colorEntry;
}

void RobotGui::WidgetSettingsDialog::addEntry(const std::string &title, QWidget *wid) {
    dialogLayout->addWidget(new QLabel(title.c_str()), nextRow, 0);
    dialogLayout->addWidget(wid, nextRow, 1);
    nextRow++;
}


