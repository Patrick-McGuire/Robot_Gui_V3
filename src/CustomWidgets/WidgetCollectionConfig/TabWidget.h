#ifndef ROBOT_GUI_V3_TABWIDGET_H
#define ROBOT_GUI_V3_TABWIDGET_H

#include "../BaseStructure/BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include <string>
#include "../../WidgetData.h"
#include "../../RobotGui.h"
#include "../../Config/XMLInput.h"
#include <QTabWidget>
#include <QString>
#include "../../GUIMaker.h"
#include <QApplication>
#include "../../Theme.h"
#include "../../Config/XMLOutput.h"
#include "../../WidgetData.h"
#include "WidgetCollectionConfig.h"

class XMLOutput;
class WidgetCollectionConfig;
namespace RobotGui {

    /**
         * @class TabWidget
         * Custom QWidget that creates tabs with children widgets
         *
         * @author Patrick McGuire (Patrick-McGuire)
         */
    class TabWidget : public BaseWidget  {
    public:
        /**
         * Constructor
         * @param parent QWidget to make parent
         * @param configInfo configuration data
         * @param widgetData global widgetData object
         */
        TabWidget(QWidget *parent, const WidgetBaseConfig::SharedPtr& configInfo, WidgetData *widgetData, Theme *_theme);

        ~TabWidget();

    private:
        QGridLayout layout;
        QTabWidget *tabs;
        std::vector<QWidget*> pages;
        std::vector<std::vector<BaseWidget*>> widgets;
        std::shared_ptr<WidgetCollectionConfig> widgetCollectionConfig;

        /**
         * Update the widget when in focus
         */
        void updateInFocus() override;

        /**
         * Update the widget when not in focus
         */
        void updateNoFocus() override;

        /**
         * Update the widget when coming into focus
         */
        void updateOnInFocus() override;

        /**
         * Sets draggability of all children
         * @param _draggable weather or not children should be draggable
         */
        void customUpdateDraggability(bool _draggable) override;

        /**
         * Updates the style of this widget
         * @param overwrite if we should overwrite any attributes with theme
         */
        void customUpdateStyle() override;

        /**
         * Updates the style of this children widgets
         * @param overwrite if we should overwrite any attributes with theme
         */
        void updateChildrenStyle() override;
    };
}


#endif //ROBOT_GUI_V3_TABWIDGET_H
