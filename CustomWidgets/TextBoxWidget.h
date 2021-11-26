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

class TextBoxWidget: public BaseWidget  {
private:
    QLabel *textBox;
    QLabel *titleBox;
    QGridLayout *layout;

    std::vector<std::string> lineKeys;

    std::string GetInfoString();
public:
    /**
     * Constructor
     * @param name  name of widget
     * @param x     x position of the widget
     * @param y     y position of the widget
     */
    TextBoxWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData);

    static void parseXml(const WidgetConfig_ptr& parentConfig, rapidxml::xml_node<> *node);

    void updateInFocus() override;
    void updateNoFocus() override;
    void updateOnInFocus() override;
    void customUpdate() override;

    // Style
    void customUpdateStyle(bool overwrite) override;


    /**
     * Updates the text color of this widget
     * @param overwrite weather to overwrite any attributes with theme
     */
    void updateTextColor(bool overwrite) override;

    /**
     * Updates the header text color of this widget
     * @param overwrite weather to overwrite any attributes with theme
     */
    void updateHeaderTextColor(bool overwrite) override;

    /**
     * Updates the widget background color of this widget
     * @param overwrite weather to overwrite any attributes with theme
     */
    void updateWidgetBackgroundColor(bool overwrite) override;
};

#endif //ROBOT_GUI_V3_TEXTBOXWIDGET_H
