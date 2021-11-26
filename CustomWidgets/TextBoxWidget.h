#ifndef ROBOT_GUI_V3_TEXTBOXWIDGET_H
#define ROBOT_GUI_V3_TEXTBOXWIDGET_H
#include "BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include "../ConfigStructs.h"
#include <string>
#include "../WidgetData.h"
#include "../Constants.h"
#include "../XML/XMLConstants.h"
#include "../Theme.h"

#define textBoxTittleBoxName "TITTLE_BOX"
#define textBoxTextBoxName "TEXT_BOX"

/**
 * @class TextBoxWidget
 * Custom QWidget that creates tabs with children widgets
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class TextBoxWidget: public BaseWidget  {
public:
    /**
     * Constructor
     * @param parent QWidget to make parent
     * @param configInfo configuration data
     * @param widgetData global widgetData object
     */
    TextBoxWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData);

    /**
     * Parses a xml node into the config struct
     * @param parentConfig[out] struct to store data into
     * @param node[in] xml node to parse
     */
    static void parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);

private:
    QLabel *textBox;
    QLabel *titleBox;
    QGridLayout *layout;
    std::vector<std::string> lineKeys;

    /**
     * Returns the string for the text box based on widgetData
     * @return string to display
     */
    std::string GetInfoString();

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
     * Helper function for updating data
     */
    void customUpdate() override;

    /**
     * Updates the style of this widget
     * @param overwrite if we should overwrite any attributes with theme
     */
    void customUpdateStyle(bool overwrite) override;
};

#endif //ROBOT_GUI_V3_TEXTBOXWIDGET_H
