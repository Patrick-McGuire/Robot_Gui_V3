#ifndef ROBOT_GUI_V3_SIMPLEBUTTONWIDGET_H
#define ROBOT_GUI_V3_SIMPLEBUTTONWIDGET_H
#include "BaseWidget.h"
#include <QWidget>
#include <string>
#include <QPushButton>
#include "../ConfigStructs.h"
#include "../WidgetData.h"
#include "../Constants.h"
#include "../XML/XMLConstants.h"
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
    SimpleButtonWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData);

    /**
     * Parses a xml node into the config struct
     * @param parentConfig[out] struct to store data into
     * @param node[in] xml node to parse
     */
     static void parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);

private slots:
    void onClick();
    void onRelease();

private:
    QPushButton *button;
    bool state = false;

    /**
     * Updates the style of this widget
     * @param overwrite if we should overwrite any attributes with theme
     */
    void customUpdateStyle(bool overwrite) override;
};


#endif //ROBOT_GUI_V3_SIMPLEBUTTONWIDGET_H
