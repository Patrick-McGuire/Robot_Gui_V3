#include "LineConfig.h"
#include "LineEntry.h"

//////// Mandatory constructors ////////
RobotGui::LineConfig::LineConfig(WidgetConstants::Type _type) : WidgetBaseConfig(_type) {}

RobotGui::LineConfig::SharedPtr RobotGui::LineConfig::create(WidgetConstants::Type _type) {
    return RobotGui::LineConfig::SharedPtr(new LineConfig(_type));
}

RobotGui::LineConfig::SharedPtr RobotGui::LineConfig::create(const std::string &_type) {
    return RobotGui::LineConfig::SharedPtr(new LineConfig(WidgetConstants::getWidgetType(_type)));
}

RobotGui::LineConfig::SharedPtr RobotGui::LineConfig::create() {
    return RobotGui::LineConfig::SharedPtr(new LineConfig(RobotGui::WidgetConstants::NO_TYPE));
}
////////   ////////


void RobotGui::LineConfig::parseXml(rapidxml::xml_node<> *node) {
    // Iterate though all lines
    for (auto *line = node->first_node(); line; line = line->next_sibling()) {
        std::string tagName = line->name();
        if (tagName == RobotGui::Xml::LINE_TAG) {
            LineInfo configStruct;
            for (rapidxml::xml_attribute<> *attr = line->first_attribute(); attr; attr = attr->next_attribute()) {
                std::string attrName = attr->name();
                std::string attrVal = attr->value();

                if (attrName == RobotGui::Xml::TYPE_ATR) {
                    configStruct.type = attrVal;
                } else if (attrName == RobotGui::Xml::SOURCE_ATR || attrName == RobotGui::Xml::VALUE_ATR) {
                    configStruct.source = attrVal;
                } else if (attrName == RobotGui::Xml::TITLE_ATR || attrName == RobotGui::Xml::LABEL_ATR) {
                    configStruct.label = attrVal;
                } else if (attrName == RobotGui::Xml::MINIMUM_ATR) {
                    configStruct.min = std::atof(attrVal.c_str());
                } else if (attrName == RobotGui::Xml::MAXIMUM_ATR) {
                    configStruct.max = std::atof(attrVal.c_str());
                } else if (attrName == RobotGui::Xml::COLOR_ATR) {
                    configStruct.color = attrVal;
                }
            }
            lines.push_back(configStruct);
        }
    }
}

void RobotGui::LineConfig::outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) {
    for (auto &lineInfo: lines) {
        // Allocate line node
        rapidxml::xml_node<> *line = doc->allocate_node(rapidxml::node_element, RobotGui::Xml::LINE_TAG);
        node->append_node(line);
        // Add line attributes
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::LABEL_ATR, lineInfo.label.c_str()));
        line->append_attribute(doc->allocate_attribute(RobotGui::Xml::VALUE_ATR, lineInfo.source.c_str()));
        if (lineInfo.color.is_initialized()) {
            line->append_attribute(doc->allocate_attribute(RobotGui::Xml::COLOR_ATR, lineInfo.color->c_str()));
        }
        if (lineInfo.type.is_initialized()) {
            line->append_attribute(doc->allocate_attribute(RobotGui::Xml::TYPE_ATR, lineInfo.type->c_str()));
        }
        if (lineInfo.min.is_initialized()) {
            line->append_attribute(doc->allocate_attribute(RobotGui::Xml::MINIMUM_ATR, doc->allocate_string(std::to_string(lineInfo.min.get()).c_str())));
        }
        if (lineInfo.max.is_initialized()) {
            line->append_attribute(doc->allocate_attribute(RobotGui::Xml::MAXIMUM_ATR, doc->allocate_string(std::to_string(lineInfo.max.get()).c_str())));
        }
    }
}

void RobotGui::LineConfig::customCreateDialog(RobotGui::WidgetSettingsDialog *dialog) {
    auto holder = new QWidget();
    auto layout = new QVBoxLayout();
    holder->setLayout(layout);
    layout->setMargin(0);
    layout->addWidget(new QLabel("Label:    Source:    Color:    Type:    Min:    Max:"));

    for (int i = 0; i < lines.size(); i++) {
        auto row = lines[i];
        auto line = new LineEntry();
        line->setLineInfo(&row.label, &row.source, &row.color, &row.type, &row.min, &row.max);
        layout->addWidget(line);
        LineInfo *info = &lines[i];
        connect(line, &LineEntry::deleted, this, [this, i] { removeRow(i); });
        connect(line, &LineEntry::updated, this, [this, info] { updateRow(info); });
    }
    auto addBut = new QPushButton("+");
    addBut->setFixedWidth(25);
    layout->addWidget(addBut);
    dialog->addEntry("Lines:", holder);
    connect(addBut, &QPushButton::clicked, this, [this, layout] { addRow(layout); });
}

void RobotGui::LineConfig::addRow(QVBoxLayout *layout) {
    lines.push_back(getDefault());
    auto line = new LineEntry();
    LineInfo row = lines[lines.size() - 1];
    line->setLineInfo(&row.label, &row.source, &row.color, &row.type, &row.min, &row.max);
    int index = layout->count() - 1;
    layout->insertWidget(index, line);
    LineInfo *info = &lines[lines.size() - 1];
    connect(line, &LineEntry::deleted, this, [this, index] { removeRow(index); });
    connect(line, &LineEntry::updated, this, [this, info] { updateRow(info); });

}

void RobotGui::LineConfig::removeRow(int index) {
    qobject_cast<LineEntry *>(sender())->hide();
    lines.erase(lines.begin() + index);
}

void RobotGui::LineConfig::updateRow(LineInfo *row) {
    (row->label) = qobject_cast<LineEntry *>(sender())->label->text().toStdString();
    (row->source) = qobject_cast<LineEntry *>(sender())->source->text().toStdString();
    if (row->color.is_initialized()) { (row->color) = qobject_cast<LineEntry *>(sender())->color->text().toStdString(); }
    if (row->type.is_initialized()) { (row->type) = qobject_cast<LineEntry *>(sender())->type->text().toStdString(); }
    if (row->min.is_initialized()) { try { (row->min) = std::stod(qobject_cast<LineEntry *>(sender())->min->text().toStdString()); } catch (...) {}}
    if (row->max.is_initialized()) { try { (row->max) = std::stod(qobject_cast<LineEntry *>(sender())->max->text().toStdString()); } catch (...) {}}
}

RobotGui::LineConfig::LineInfo RobotGui::LineConfig::getDefault() {
    LineInfo newConfig;
    for(const auto& line : lines) {
        if(line.color.is_initialized()) { newConfig.color = ""; }
        if(line.type.is_initialized()) { newConfig.type = ""; }
        if(line.min.is_initialized()) { newConfig.min = 0; }
        if(line.max.is_initialized()) { newConfig.max = 0; }
    }
    return newConfig;
}


