#include "LivePlotWidget.h"
#include "../../../lib/CommonFunctions.h"
#include "QGridLayout"
#include "../../WidgetData.h"
#include "../../InternalJson.h"
#include "../../Theme.h"
#include "../BaseStructure/BaseWidget.h"
#include "LineConfig.h"

/**
 * Height/Width
 * Autoscaling/Fixed range/Never scale down
 *
 */


RobotGui::LivePlotWidget::LivePlotWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) :
        BaseWidget(parent, configInfo, widgetData, _theme) {

    configInfo->require(WidgetConstants::TITLE, "NO TITTLE");
    configInfo->require(WidgetConstants::BACKGROUND_COLOR);
    configInfo->require(WidgetConstants::HEADER_COLOR);
    configInfo->require(WidgetConstants::TEXT_COLOR);
    configInfo->require(WidgetConstants::RANGE, 10.0);
    configInfo->require(WidgetConstants::HEIGHT, 200);
    configInfo->require(WidgetConstants::WIDTH, 200);
    configInfo->require(WidgetConstants::MIN, RobotGui::Xml::AUTO_CONST);
    configInfo->require(WidgetConstants::MAX, RobotGui::Xml::AUTO_CONST);

    lineConfig = std::dynamic_pointer_cast<LineConfig>(configInfo);

    // Create the chart
    chart = new QChart();
    chart->layout()->setContentsMargins(0, 0, 0, 0);

    chartView = new QChartView(chart);
    chartView->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    auto layout = new QGridLayout();
    layout->addWidget(chartView);
    layout->setMargin(1);
    setLayout(layout);

    top = new QWidget(this);

    pauseButton = new QPushButton("Pause", top);
    pauseButton->setObjectName(this->objectName() + "_PAUSE_BUTTON");
    pauseButton->move(1, 1);
    resetButton = new QPushButton("Reset", top);
    resetButton->setObjectName(this->objectName() + "_RESET_BUTTON");
    connect(resetButton, SIGNAL(pressed()), this, SLOT(reset()));
    connect(pauseButton, SIGNAL(pressed()), this, SLOT(pause()));



    customUpdateFromConfigInfo();
}

void RobotGui::LivePlotWidget::customUpdateFromConfigInfo() {
    chart->removeAllSeries();
    allSeries.clear();

    // Add all series that we need
    for (auto &line: lineConfig->lines) {
        auto series = new QLineSeries();
        series->setName(line.label.c_str());
        if (line.color) { series->setColor(line.color->c_str()); }
        data.emplace_back();
        chart->addSeries(series);
        allSeries.push_back(series);
    }
    chart->createDefaultAxes();


    chartView->setFixedSize(configInfo->width.get(), configInfo->height.get());
    top->setFixedSize(configInfo->width.get(), configInfo->height.get());
    resetButton->move(configInfo->width.get() - resetButton->width() + 10, 1);
    this->adjustSize();


    chart->setTitle(configInfo->title->c_str());

    if (!chart->axes(Qt::Horizontal).empty()) {
        chart->axes(Qt::Horizontal)[0]->setMax(0);
        chart->axes(Qt::Horizontal)[0]->setMin(-lineConfig->range.get());
    }
    if (!chart->axes(Qt::Vertical).empty()) {
        if (!lineConfig->max.is_initialized()) {
            autoRangeMax = true;
        } else {
            try {
                rangeMax = std::stoi(lineConfig->max.get());
                autoRangeMax = false;
                chart->axes(Qt::Vertical)[0]->setMax(rangeMax);
            } catch (...) {
                autoRangeMax = true;
            }
        }
        if (!lineConfig->min.is_initialized()) {
            autoRangeMin = true;
        } else {
            try {
                rangeMin = std::stoi(lineConfig->min.get());
                autoRangeMin = false;
                chart->axes(Qt::Vertical)[0]->setMin(rangeMin);
            } catch (...) {
                autoRangeMin = true;
            }
        }
    }
    updateStyle();
}


void RobotGui::LivePlotWidget::customUpdateStyle() {
    chart->setBackgroundBrush(CommonFunctions::GetQColorFromString(getWidgetBackgroundColor()));
    chart->setTitleBrush(CommonFunctions::GetQColorFromString(getHeaderColor()));
    chart->legend()->setLabelColor(CommonFunctions::GetQColorFromString(getTextColor()));

    std::string gridLineColor = CommonFunctions::GenerateDarkerColor(getBackgroundColor(), 30 * (theme->isLight() ? 1 : -1));
    if (!chart->axes(Qt::Vertical).empty()) {
        auto verticalAxis = chart->axes(Qt::Vertical)[0];
        verticalAxis->setGridLinePen(CommonFunctions::GetQColorFromString(gridLineColor));
        verticalAxis->setLinePen(CommonFunctions::GetQColorFromString(CommonFunctions::GetContrastingTextColor(getWidgetBackgroundColor())));
        verticalAxis->setLabelsBrush(CommonFunctions::GetQColorFromString(getTextColor()));
    }
    if (!chart->axes(Qt::Horizontal).empty()) {
        auto horizontalAxis = chart->axes(Qt::Horizontal)[0];
        horizontalAxis->setGridLinePen(CommonFunctions::GetQColorFromString(gridLineColor));
        horizontalAxis->setLinePen(CommonFunctions::GetQColorFromString(CommonFunctions::GetContrastingTextColor(getWidgetBackgroundColor())));
        horizontalAxis->setLabelsBrush(CommonFunctions::GetQColorFromString(getTextColor()));
    }
    char buf[400];
    sprintf(buf, "QWidget#%s{ background: %s; color: %s }",
            pauseButton->objectName().toStdString().c_str(),
            getBackgroundColor().c_str(),
            getHeaderColor().c_str()
    );
    pauseButton->setStyleSheet(buf);
    memset(buf, 0, strlen(buf));
    sprintf(buf, "QWidget#%s{ background: %s; color: %s }",
            resetButton->objectName().toStdString().c_str(),
            getBackgroundColor().c_str(),
            getHeaderColor().c_str()
    );
    resetButton->setStyleSheet(buf);
}

void RobotGui::LivePlotWidget::generateGraph() {
    if (pauseState) { return; }
    double max = data[0].back().second;
    double min = data[0].back().second;
    for (int i = 0; i < allSeries.size(); i++) {
        allSeries[i]->clear();
        double firstTime = data[i].back().first;
        for (auto &el: data[i]) {
            allSeries[i]->append(el.first - firstTime, el.second);
            if (el.second > max) { max = el.second; }
            if (el.second < min) { min = el.second; }
        }
    }
    autoRange(min, max, 0);
}

void RobotGui::LivePlotWidget::updateInFocus() {
    chart->update();
    for (const auto &line: lineConfig->lines) {
        if (widgetData->keyUpdated(line.source)) {
            updateDataStructure();
            if (graphIsReady()) {
                generateGraph();
            }
            return;
        }
    }
}

void RobotGui::LivePlotWidget::updateNoFocus() {
    for (const auto& line: lineConfig->lines) {
        if (widgetData->keyUpdated(line.source)) {
            updateDataStructure();
            return;
        }
    }
}

void RobotGui::LivePlotWidget::updateOnInFocus() {
    updateDataStructure();
    generateGraph();
}

void RobotGui::LivePlotWidget::autoRange(double min, double max, double time) {
    if (autoRangeMin) {
        chart->axes(Qt::Vertical)[0]->setMin(min);
    }
    if (autoRangeMax) {
        chart->axes(Qt::Vertical)[0]->setMax(max);
    }
}

void RobotGui::LivePlotWidget::updateDataStructure() {
    for (int i = 0; i < lineConfig->lines.size(); i++) {
        RobotGui::InternalJson::SharedPtr json = widgetData->getJson()->mapGet(lineConfig->lines[i].source);
        double val = 0;
        if (json->getType() == RobotGui::InternalJson::double_t) {
            val = json->getDouble();
        } else if (json->getType() == RobotGui::InternalJson::int_t) {
            val = json->getInt();
        } else if (json->getType() == RobotGui::InternalJson::bool_t) {
            val = json->getBool();
        }
        double time = CommonFunctions::getEpochTime();
        data[i].emplace_back(time, val);
        while (time - data[i].front().first > lineConfig->range) {
            data[i].pop_front();
        }
    }
}

bool RobotGui::LivePlotWidget::graphIsReady() {
    if (maxSpeed) { return true; }
    double time = CommonFunctions::getEpochTime();
    if (time - lastTime > minUpdateTime) {
        lastTime = time;
        return true;
    }
    return false;
}

void RobotGui::LivePlotWidget::reset() {
    for (int i = 0; i < lineConfig->lines.size(); i++) {
        while (!data[i].empty()) {
            data[i].pop_front();
        }
    }
}

void RobotGui::LivePlotWidget::pause() {
    pauseState = !pauseState;
    pauseButton->setText(pauseState ? "Play" : "Pause");
}


