//
// Created by nathan on 12/29/21.
//

#ifndef ROBOT_GUI_V3_DROPDOWNTEXTBOXWIDGET_H
#define ROBOT_GUI_V3_DROPDOWNTEXTBOXWIDGET_H

#include "BaseStructure/BaseWidget.h"

#include <QComboBox>

#include "WidgetParts/LineTextDisplay.h"
#include "../WidgetData.h"
#include "../Theme.h"

namespace RobotGui {
    class DropDownTextBoxWidget : public BaseWidget {
    public:
        DropDownTextBoxWidget(QWidget *parent, const WidgetBaseConfig::SharedPtr &configInfo, WidgetData *widgetData, Theme *theme);

        void updateInFocus() override;

        void setDropDownItems(std::vector<std::string> keys);

        void customUpdateStyle() override;

    protected:
        QComboBox *selectionBox;
        LineTextDisplay *textDisplay;
    };
}

#endif //ROBOT_GUI_V3_DROPDOWNTEXTBOXWIDGET_H
