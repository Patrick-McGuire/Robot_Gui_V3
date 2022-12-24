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

void RobotGui::WidgetBaseConfig::parseXml(rapidxml::xml_node<> *node) {}

void RobotGui::WidgetBaseConfig::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {}

void RobotGui::WidgetBaseConfig::customCreateDialog(WidgetSettingsDialog *dialog) {}

void RobotGui::WidgetBaseConfig::set(RobotGui::WidgetConstants::Attribute attr, bool boolVal, int intVal, double doubleVal, std::string strVal, std::string defStyle, bool overwrite) {
    switch (attr) {
        case WidgetConstants::TITLE:
            if (!title || overwrite) { title = strVal; }
            break;
        case WidgetConstants::SOURCE:
            if (!source || overwrite) { source = strVal; }
            break;
        case WidgetConstants::HEIGHT:
            if (!height || overwrite) { height = intVal; }
            break;
        case WidgetConstants::WIDTH:
            if (!width || overwrite) { width = intVal; }
            break;
        case WidgetConstants::SIZE:
            if (!size || overwrite) { size = intVal; }
            break;
        case WidgetConstants::MIN:
            if (!min || overwrite) { min = strVal; }
            break;
        case WidgetConstants::MAX:
            if (!max || overwrite) { max = strVal; }
            break;
        case WidgetConstants::RANGE:
            if (!range || overwrite) { range = doubleVal; }
            break;
        case WidgetConstants::ROW_NUMBER:
            if (!rowNumber || overwrite) { rowNumber = intVal; }
            break;
        case WidgetConstants::COLUMN_NUMBER:
            if (!columnNumber || overwrite) { columnNumber = intVal; }
            break;
        case WidgetConstants::FONT:
            if (!font || overwrite) { font = defStyle; }
            break;
        case WidgetConstants::BACKGROUND_COLOR:
            if (!backgroundColor || overwrite) { backgroundColor = defStyle; }
            break;
        case WidgetConstants::FOREGROUND_COLOR:
            if (!foregroundColor || overwrite) { foregroundColor = defStyle; }
            break;
        case WidgetConstants::RELIEF:
            if (!relief || overwrite) { relief = defStyle; }
            break;
        case WidgetConstants::TEXT_COLOR:
            if (!textColor || overwrite) { textColor = defStyle; }
            break;
        case WidgetConstants::HEADER_COLOR:
            if (!headerColor || overwrite) { headerColor = defStyle; }
            break;
        case WidgetConstants::BORDER_COLOR:
            if (!borderColor || overwrite) { borderColor = defStyle; }
            break;
        case WidgetConstants::FONT_Size:
            if (!fontSize || overwrite) { fontSize = intVal; }
            break;
        case WidgetConstants::BORDER_Width:
            if (!borderWidth || overwrite) { borderWidth = intVal; }
            break;
    }
}

void RobotGui::WidgetBaseConfig::require(WidgetConstants::Attribute attr, bool defBool, int defInt, double defDouble, const std::string &defString, const std::string &defStyle) {
    set(attr, defBool, defInt, defDouble, defString, defStyle, false);
    requiredAttributes.insert(attr);
}

bool RobotGui::WidgetBaseConfig::isRequired(WidgetConstants::Attribute attr) {
    return requiredAttributes.find(attr) != requiredAttributes.end();
}

void RobotGui::WidgetBaseConfig::require(RobotGui::WidgetConstants::Attribute attr) {
    require(attr, false, 0, 0, "", RobotGui::Xml::THEME_CONST);
}

void RobotGui::WidgetBaseConfig::require(RobotGui::WidgetConstants::Attribute attr, int def) {
    require(attr, false, def, def, "", RobotGui::Xml::THEME_CONST);
}

void RobotGui::WidgetBaseConfig::require(RobotGui::WidgetConstants::Attribute attr, double def) {
    require(attr, false, (int) def, def, "", RobotGui::Xml::THEME_CONST);
}

void RobotGui::WidgetBaseConfig::require(RobotGui::WidgetConstants::Attribute attr, const std::string &def) {
    require(attr, false, 0, 0, def, RobotGui::Xml::THEME_CONST);
}











////////////// Dialog stuff


//void RobotGui::WidgetBaseConfig::onEdit(std::string *val) {
//    (*val) = qobject_cast<QLineEdit *>(sender())->text().toStdString();
//    emit configChanged();
//}
//
//void RobotGui::WidgetBaseConfig::onColorEdit(std::string *val) {
//    (*val) = qobject_cast<ColorEntry *>(sender())->getColor();
//    emit configChanged();
//}

void RobotGui::WidgetBaseConfig::createDialog(WidgetSettingsDialog *dialog) {
//    addDialogOption(dialog, "Draggable:", &draggable);
//    addDialogOption(dialog, "X pos:", &x);
//    addDialogOption(dialog, "Y pos:", &y);
//    if (isRequired(WidgetConstants::TITLE)) { addDialogOption(dialog, "Title:", &title.get()); }
//    if (isRequired(WidgetConstants::SOURCE)) { addDialogOption(dialog, "Source:", &source.get()); }
//    if (isRequired(WidgetConstants::HEIGHT)) { addDialogOption(dialog, "Height:", &height.get()); }
//    if (isRequired(WidgetConstants::WIDTH)) { addDialogOption(dialog, "Width:", &width.get()); }
//    if (isRequired(WidgetConstants::SIZE)) { addDialogOption(dialog, "Size:", &size.get()); }
//    if (isRequired(WidgetConstants::MIN)) { addDialogOption(dialog, "Min:", &min.get()); }
//    if (isRequired(WidgetConstants::MAX)) { addDialogOption(dialog, "Max:", &max.get()); }
//    if (isRequired(WidgetConstants::RANGE)) { addDialogOption(dialog, "Range:", &range.get()); }
//    if (isRequired(WidgetConstants::ROW_NUMBER)) { addDialogOption(dialog, "Row number:", &rowNumber.get()); }
//    if (isRequired(WidgetConstants::COLUMN_NUMBER)) { addDialogOption(dialog, "Column number:", &columnNumber.get()); }
//    // Style
//    if (isRequired(WidgetConstants::BACKGROUND_COLOR)) { addDialogColorOption(dialog, "Background color", &backgroundColor.get()); }
//    if (isRequired(WidgetConstants::TEXT_COLOR)) { addDialogColorOption(dialog, "Text color", &textColor.get()); }
//    if (isRequired(WidgetConstants::HEADER_COLOR)) { addDialogColorOption(dialog, "Header color", &headerColor.get()); }
//    if (isRequired(WidgetConstants::BORDER_COLOR)) { addDialogColorOption(dialog, "Border color", &borderColor.get()); }
//    customCreateDialog(dialog);
}

void RobotGui::WidgetBaseConfig::showEditMenu() {
//    auto dialog = new WidgetSettingsDialog();
//    connect(this, SIGNAL(destroyed()), dialog, SLOT(close()));
//    createDialog(dialog);
//    dialog->show();
}

//void RobotGui::WidgetBaseConfig::onEdit(int *val) {
//    try { (*val) = std::stoi(qobject_cast<QLineEdit *>(sender())->text().toStdString()); } catch (...) {}
//    emit configChanged();
//}
//
//void RobotGui::WidgetBaseConfig::onEdit(double *val) {
//    try { (*val) = std::stod(qobject_cast<QLineEdit *>(sender())->text().toStdString()); } catch (...) {}
//    emit configChanged();
//}
//
//void RobotGui::WidgetBaseConfig::onEdit(bool *val) {
//    (*val) = qobject_cast<QCheckBox *>(sender())->isChecked();
//    emit configChanged();
//}
//
//void RobotGui::WidgetBaseConfig::addDialogOption(WidgetSettingsDialog *dialog, const std::string &_title, std::string *varLoc) {
//    connect(dialog->addTextEntry(_title, *varLoc), &QLineEdit::textEdited, this, [this, varLoc] { onEdit(varLoc); });
//}
//
//void RobotGui::WidgetBaseConfig::addDialogOption(WidgetSettingsDialog *dialog, const std::string &_title, int *varLoc) {
//    connect(dialog->addIntEntry(_title, *varLoc), &QLineEdit::textEdited, this, [this, varLoc] { onEdit(varLoc); });
//}
//
//void RobotGui::WidgetBaseConfig::addDialogOption(WidgetSettingsDialog *dialog, const std::string &_title, double *varLoc) {
//    connect(dialog->addDoubleEntry(_title, *varLoc), &QLineEdit::textEdited, this, [this, varLoc] { onEdit(varLoc); });
//}
//
//void RobotGui::WidgetBaseConfig::addDialogOption(WidgetSettingsDialog *dialog, const std::string &_title, bool *varLoc) {
//    connect(dialog->addBoolEntry(_title, *varLoc), &QPushButton::clicked, this, [this, varLoc] { onEdit(varLoc); });
//}
//
//void RobotGui::WidgetBaseConfig::addDialogColorOption(RobotGui::WidgetSettingsDialog *dialog, const std::string &_title, std::string *varLoc) {
//    ColorEntry *colorEntry = dialog->addColorEntry(_title, *varLoc);
//    connect(colorEntry, &ColorEntry::updated, this, [this, varLoc] { onColorEdit(varLoc); });
//}



