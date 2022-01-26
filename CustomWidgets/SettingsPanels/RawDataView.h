//
// Created by nathan on 1/26/22.
//

#ifndef ROBOT_GUI_V3_RAWDATAVIEW_H
#define ROBOT_GUI_V3_RAWDATAVIEW_H

#include "BaseSettingsPanel.h"

#include <QLabel>

#include "../WidgetParts/LineTextDisplay.h"

class RawDataView : public BaseSettingsPanel {
public:
    RawDataView(QWidget *parent, WidgetData *widgetData, Theme *theme);

    void updateInFocus() override;

    void customUpdateStyle() override ;

private:
    LineTextDisplay *lineTextDisplay;
};


#endif //ROBOT_GUI_V3_RAWDATAVIEW_H
