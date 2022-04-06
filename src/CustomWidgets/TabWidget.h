#ifndef ROBOT_GUI_V3_TABWIDGET_H
#define ROBOT_GUI_V3_TABWIDGET_H

#include "BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include <string>
#include "../WidgetData.h"
#include "../RobotGui.h"
#include "../Config/XMLInput.h"
#include <QTabWidget>
#include <QString>
#include "../GUIMaker.h"
#include <QApplication>
#include "../Theme.h"
#include "../Config/XMLOutput.h"
#include "../WidgetData.h"

class XMLOutput;

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
    TabWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr& configInfo, RobotGui::WidgetData *widgetData, Theme *_theme);

    /**
     * Parses a xml node into the config struct
     * @param parentConfig[out] struct to store data into
     * @param node[in] xml node to parse
     */
    static void parseXml(const RobotGui::WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);


    /**
     * Saves any configuration data to a xml node
     * @param node node to output to
     */
    void outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) override;

private:
    QGridLayout layout;
    QTabWidget *tabs;
    std::vector<QWidget*> pages;
    std::vector<std::vector<BaseWidget*>> widgets;

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

    /**
     * Parses xml for all children in the tab
     * @param parentConfig tab configuration to add children to
     * @param node xml node containing children
     */
    static void parseTabChildren(const RobotGui::WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);
};


#endif //ROBOT_GUI_V3_TABWIDGET_H
