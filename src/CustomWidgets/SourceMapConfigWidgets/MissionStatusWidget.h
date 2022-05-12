#ifndef ROBOT_GUI_V3_MISSIONSTATUSWIDGET_H
#define ROBOT_GUI_V3_MISSIONSTATUSWIDGET_H

#include "../BaseStructure/BaseWidget.h"
#include "../../WidgetData.h"
#include "../../Theme.h"
#include <QLabel>
#include "SourceMapConfig.h"

namespace RobotGui {
    class MissionStatusWidget : public BaseWidget {
    public:
        MissionStatusWidget(QWidget *parent, const WidgetBaseConfig::SharedPtr &configInfo, WidgetData *widgetData, Theme *theme);

        void updateInFocus() override;

        void customUpdateStyle() override ;

    protected:
        std::string statusSource;
        std::string missionNameSource;
        std::string objectiveSource;
        int size;

        QLabel *statusBox;
        QLabel *missionNameBox;
        QLabel *objectiveBox;

        SourceMapConfig::SharedPtr sourceMapConfig;
    };
}


#endif //ROBOT_GUI_V3_MISSIONSTATUSWIDGET_H
