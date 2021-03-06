#ifndef ROBOT_GUI_V3_ROVSTATUSWIDGET_H
#define ROBOT_GUI_V3_ROVSTATUSWIDGET_H

#include "../BaseStructure/BaseWidget.h"
#include "../../WidgetData.h"
#include "../../Theme.h"
#include "SourceMapConfig.h"
#include <QLabel>

namespace RobotGui {
    class ROVStatusWidget : public BaseWidget {
    public:
        ROVStatusWidget(QWidget *parent, const WidgetBaseConfig::SharedPtr &configInfo, WidgetData *widgetData, Theme *theme);

        void updateInFocus() override;

        void customUpdateStyle() override;

    protected:
        std::string statusSource;
        std::string armedSource;
        std::string allowedToArmSource;
        std::string modeSource;
        std::string runtimeSource;
        std::string timeSource;
        int size;

        QLabel *statusBox;
        QLabel *armingBox;
        QLabel *modeBox;
        QLabel *timeBox;
        QLabel *runtimeBox;

        SourceMapConfig::SharedPtr sourceMapConfig;
    };
}


#endif //ROBOT_GUI_V3_ROVSTATUSWIDGET_H
