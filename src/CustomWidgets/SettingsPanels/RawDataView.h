//
// Created by nathan on 1/26/22.
//

#ifndef ROBOT_GUI_V3_RAWDATAVIEW_H
#define ROBOT_GUI_V3_RAWDATAVIEW_H

#include "BaseSettingsPanel.h"

#include <QLabel>
#include <QScrollArea>

#include "../WidgetParts/LineTextDisplay.h"
#include "../../WidgetData.h"

class RawDataView : public BaseSettingsPanel {
public:
    RawDataView(QWidget *parent, RobotGui::WidgetData *widgetData, Theme *theme);

    void updateInFocus() override;

    void customUpdateStyle() override;

private:
    LineTextDisplay *lineTextDisplay;
    QScrollArea *scrollArea;
};


#endif //ROBOT_GUI_V3_RAWDATAVIEW_H
