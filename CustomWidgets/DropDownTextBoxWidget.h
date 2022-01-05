//
// Created by nathan on 12/29/21.
//

#ifndef ROBOT_GUI_V3_DROPDOWNTEXTBOXWIDGET_H
#define ROBOT_GUI_V3_DROPDOWNTEXTBOXWIDGET_H

#include "BaseWidget.h"

#include <QComboBox>

#include "WidgetParts/LineTextDisplay.h"

class DropDownTextBoxWidget : public BaseWidget {
public:
    DropDownTextBoxWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme);

    void updateInFocus() override;

    void setDropDownItems(std::vector<std::string> keys);

    void customUpdateStyle();

protected:
    QComboBox *selectionBox;
    LineTextDisplay *textDisplay;
};

#endif //ROBOT_GUI_V3_DROPDOWNTEXTBOXWIDGET_H