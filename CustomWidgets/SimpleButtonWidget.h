#ifndef ROBOT_GUI_V3_SIMPLEBUTTONWIDGET_H
#define ROBOT_GUI_V3_SIMPLEBUTTONWIDGET_H
#include "BaseWidget.h"
#include <QWidget>
#include <string>
#include <QPushButton>
#include "../WidgetData.h"
#include "../RobotGui.h"
#include "../Theme.h"

#define BUTTON_WIDGET_NAME "BUTTON"

/**
 * @class SimpleButtonWidget
 * Custom QWidget button
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class SimpleButtonWidget : public BaseWidget {
Q_OBJECT
public:
    /**
     * Constructor
     * @param parent QWidget to make parent
     * @param configInfo configuration data
     * @param widgetData global widgetData object
     */
    SimpleButtonWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr& configInfo, WidgetData *widgetData, Theme *_theme);

    /**
     * Parses a xml node into the config struct
     * @param parentConfig[out] struct to store data into
     * @param node[in] xml node to parse
     */
     static void parseXml(const RobotGui::WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);

private slots:
    /**
     * Onclick slot
     */
    void onClick();

    /**
     * On release slot
     */
    void onRelease();

private:
    /**
     * Updates the style of this widget
     * @param overwrite if we should overwrite any attributes with theme
     */
    void customUpdateStyle(bool overwrite) override;

    QPushButton *button;
    bool state = false;
};


#endif //ROBOT_GUI_V3_SIMPLEBUTTONWIDGET_H
