#ifndef ROBOT_GUI_V3_LIVEPLOTWIDGET_H
#define ROBOT_GUI_V3_LIVEPLOTWIDGET_H

#include "BaseWidget.h"
#include <QWidget>
#include <QLabel>
#include <string>
#include <QGridLayout>
#include <string>
#include "../WidgetData.h"
#include "../RobotGui.h"
#include "../Theme.h"
#include "QChartView"
#include "QtCharts"
#include "QLineSeries"

/**
 * @class LivePlotWidget
 * Custom QWidget that graphs data over time
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class LivePlotWidget : public BaseWidget {
Q_OBJECT
public:
    /**
     * Constructor
     * @param parent QWidget to make parent
     * @param configInfo configuration data
     * @param widgetData global widgetData object
     * @param _theme theme object
     */
    LivePlotWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme);

    /**
     * Parses a xml node into the config struct
     * @param parentConfig[out] struct to store data into
     * @param node[in] xml node to parse
     */
    static void parseXml(const RobotGui::WidgetConfig_ptr &parentConfig, rapidxml::xml_node<> *node);


    /**
     * Saves any configuration data to a xml node
     * @param node node to output to
     */
    void outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc) override;

private:
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
     * Updates the style of this widget
     * @param overwrite if we should overwrite any attributes with theme
     */
    void customUpdateStyle() override;

    void updateGraphData();

    void updateDataStructure();

    /**
     * Adjusts the range of the chart
     * @param min current min value in the chart
     * @param max current max value in the chart
     */
    void autoRange(double min, double max, double time);

    bool graphIsReady();


    /**
     * Data storage
     * First: time
     * Second: val
     */
    std::vector<std::deque<std::pair<double, double>>> data;
    double maxAll = -999999;
    double minAll = 999999;
    double minUpdateTime = .1;
    double lastTime = 0;

    bool autoRangeMin = true;
    bool autoRangeMax = true;
    double rangeMin;
    double rangeMax;

    //// QT objects
    QWidget *top;
    std::vector<QLineSeries *> allSeries;
    QChart *chart;
    QChartView *chartView;
};


#endif //ROBOT_GUI_V3_LIVEPLOTWIDGET_H