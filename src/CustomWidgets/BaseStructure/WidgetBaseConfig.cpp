#include <QLabel>
#include "WidgetBaseConfig.h"
#include "../../RobotGui.h"
#include "QDialog"
#include "QPushButton"
#include "QCheckBox"
#include "QLineEdit"
#include "WidgetSettingsDialog.h"
#include "ColorEntry.h"

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::WidgetBaseConfig::create(const std::string &_type) {
    return RobotGui::WidgetBaseConfig::SharedPtr(new WidgetBaseConfig(WidgetConstants::getWidgetType(_type)));
}

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::WidgetBaseConfig::create(WidgetConstants::Type _type) {
    return RobotGui::WidgetBaseConfig::SharedPtr(new WidgetBaseConfig(_type));
}

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::WidgetBaseConfig::create() {
    return RobotGui::WidgetBaseConfig::SharedPtr(new WidgetBaseConfig(RobotGui::WidgetConstants::NO_TYPE));
}

RobotGui::WidgetBaseConfig::WidgetBaseConfig(WidgetConstants::Type _type) : type(_type) {}

RobotGui::WidgetBaseConfig::~WidgetBaseConfig() {}

void RobotGui::WidgetBaseConfig::createDialog(WidgetSettingsDialog *dialog) {
    addDialogOption(dialog, "Draggable:", &draggable);
    addDialogOption(dialog, "X pos:", &x);
    addDialogOption(dialog, "Y pos:", &y);
    if (title.is_initialized()) { addDialogOption(dialog, "Title:", &title.get()); }
    if(source.is_initialized()) { addDialogOption(dialog, "Source:", &source.get()); }
    if(height.is_initialized()) { addDialogOption(dialog, "Height:", &height.get()); }
    if(width.is_initialized()) { addDialogOption(dialog, "Width:", &width.get()); }
    if(size.is_initialized()) { addDialogOption(dialog, "Size:", &size.get()); }
    if(min.is_initialized()) { addDialogOption(dialog, "Min:", &min.get()); }
    if(max.is_initialized()) { addDialogOption(dialog, "Max:", &max.get()); }
    if(range.is_initialized()) { addDialogOption(dialog, "Range:", &range.get()); }
    if(rowNumber.is_initialized()) { addDialogOption(dialog, "Row number:", &rowNumber.get()); }
    if(columnNumber.is_initialized()) { addDialogOption(dialog, "Column number:", &columnNumber.get()); }
    // Style
    if(backgroundColor.is_initialized()) { addDialogColorOption(dialog, "Background color", &backgroundColor.get()); }
    if(textColor.is_initialized()) { addDialogColorOption(dialog, "Text color", &textColor.get()); }
    if(headerColor.is_initialized()) { addDialogColorOption(dialog, "Header color", &headerColor.get()); }
    if(borderColor.is_initialized()) { addDialogColorOption(dialog, "Border color", &borderColor.get()); }
    customCreateDialog(dialog);
}

void RobotGui::WidgetBaseConfig::showEditMenu() {
    auto dialog = new WidgetSettingsDialog();
    connect(this, SIGNAL(destroyed()), dialog, SLOT(close()));
    createDialog(dialog);
    dialog->show();
}

void RobotGui::WidgetBaseConfig::onEdit(std::string *val) {
    (*val) = qobject_cast<QLineEdit*>(sender())->text().toStdString();
    emit configChanged();
}

void RobotGui::WidgetBaseConfig::onColorEdit(std::string *val) {
    (*val) = qobject_cast<ColorEntry*>(sender())->getColor();
    emit configChanged();
}

void RobotGui::WidgetBaseConfig::onEdit(int *val) {
    try { (*val) = std::stoi(qobject_cast<QLineEdit*>(sender())->text().toStdString()); } catch (...) {}
    emit configChanged();
}

void RobotGui::WidgetBaseConfig::onEdit(double *val) {
    try { (*val) = std::stod(qobject_cast<QLineEdit*>(sender())->text().toStdString()); } catch (...) {}
    emit configChanged();
}

void RobotGui::WidgetBaseConfig::onEdit(bool *val) {
    (*val) = qobject_cast<QCheckBox*>(sender())->isChecked();
    emit configChanged();
}

void RobotGui::WidgetBaseConfig::addDialogOption(WidgetSettingsDialog *dialog, const std::string& _title, std::string *varLoc) {
    connect(dialog->addTextEntry(_title, *varLoc), &QLineEdit::textEdited, this, [this, varLoc] { onEdit(varLoc); });
}

void RobotGui::WidgetBaseConfig::addDialogOption(WidgetSettingsDialog *dialog, const std::string& _title, int *varLoc) {
    connect(dialog->addIntEntry(_title, *varLoc), &QLineEdit::textEdited, this, [this, varLoc] { onEdit(varLoc); });
}

void RobotGui::WidgetBaseConfig::addDialogOption(WidgetSettingsDialog *dialog, const std::string& _title, double *varLoc) {
    connect(dialog->addDoubleEntry(_title, *varLoc), &QLineEdit::textEdited, this, [this, varLoc] { onEdit(varLoc); });
}

void RobotGui::WidgetBaseConfig::addDialogOption(WidgetSettingsDialog *dialog, const std::string& _title, bool *varLoc) {
    connect(dialog->addBoolEntry(_title, *varLoc), &QPushButton::clicked, this, [this, varLoc] { onEdit(varLoc); });
}

void RobotGui::WidgetBaseConfig::addDialogColorOption(RobotGui::WidgetSettingsDialog *dialog, const std::string &_title, std::string *varLoc) {
    ColorEntry *colorEntry = dialog->addColorEntry(_title, *varLoc);
    connect(colorEntry, &ColorEntry::updated, this, [this, varLoc] { onColorEdit(varLoc); });
}

void RobotGui::WidgetBaseConfig::parseXml(rapidxml::xml_node<> *node) {}

void RobotGui::WidgetBaseConfig::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {}

void RobotGui::WidgetBaseConfig::customCreateDialog(WidgetSettingsDialog *dialog) {}





