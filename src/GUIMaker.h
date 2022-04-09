#ifndef ROBOT_GUI_V3_GUIMAKER_H
#define ROBOT_GUI_V3_GUIMAKER_H

#include <vector>
#include "CustomWidgets/BaseWidget.h"
#include "CustomWidgets/TextBoxWidget.h"
#include "CustomWidgets/TabWidget.h"
#include "CustomWidgets/VideoWidget.h"
#include "CustomWidgets/SimpleButtonWidget.h"
#include "WidgetData.h"
#include "Theme.h"
#include <QWidget>
#include <QTabWidget>

namespace RobotGui {
    /**
         * @class GUIMaker
         * Static class used to generate various parts of the GUI
         *
         * @author Patrick McGuire (Patrick-McGuire)
         */
    class GUIMaker {
    public:
        /**
         * Creates a new custom widget
         * @param parent parent for the widget
         * @param configInfo configuration info for the widget
         * @param widgetData global WidgetData object
         * @param theme global theme object
         * @return new custom widget
         */
        static BaseWidget *createWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *theme);
    };
}

#endif //ROBOT_GUI_V3_GUIMAKER_H
