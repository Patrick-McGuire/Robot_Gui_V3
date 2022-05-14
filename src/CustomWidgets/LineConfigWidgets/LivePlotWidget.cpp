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


RobotGui::LivePlotWidget::LivePlotWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    styledWidgetBackgroundColor = true;
    styledHeader = true;
    styledText = true;
    configurablePos = true;
    configurableHeight = true;
    configurableWidth = true;

    if(configInfo->type == RobotGui::WidgetConstants::LIVE_PLOT) {
        lineConfig = std::dynamic_pointer_cast<LineConfig> (configInfo);
    } else {
        lineConfig = LineConfig::create();
    }

    if (!lineConfig->range.is_initialized() || lineConfig->range.get() <= 0) {
        lineConfig->range = 10;
    }
    if (!configInfo->height.is_initialized() || configInfo->height.get() <= 0) {
        configInfo->height = 200;
    }
    if (!configInfo->width.is_initialized() || configInfo->width.get() <= 0) {
        configInfo->width = 200;
    }

    chart = new QChart();
    for (auto &line: lineConfig->lines) {
        auto series = new QLineSeries();
        series->setName(line.label.c_str());
        if (line.color.is_initialized()) {
            series->setColor(line.color->c_str());
        }
        data.emplace_back();
        chart->addSeries(series);
        allSeries.push_back(series);
    }

    chart->createDefaultAxes();
    if (!chart->axes(Qt::Horizontal).empty()) {
        chart->axes(Qt::Horizontal)[0]->setMax(0);
        chart->axes(Qt::Horizontal)[0]->setMin(-lineConfig->range.get());
    }

    chartView = new QChartView(chart);
    chartView->setContentsMargins(0, 0, 0, 0);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
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
    chartView->setFixedSize(configInfo->width.get(), configInfo->height.get());
    top->setFixedSize(configInfo->width.get(), configInfo->height.get());
    resetButton->move(configInfo->width.get() - resetButton->width() + 10, 1);
    this->adjustSize();

    if(configInfo->title.is_initialized()) {
        chart->setTitle(configInfo->title.is_initialized() ? configInfo->title->c_str() : "err");
    }
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
}


void RobotGui::LivePlotWidget::customUpdateStyle() {
    chart->setBackgroundBrush(CommonFunctions::GetQColorFromString(widgetBackgroundColor));
    chart->setTitleBrush(CommonFunctions::GetQColorFromString(titleTextColor));
    chart->legend()->setLabelColor(CommonFunctions::GetQColorFromString(bodyTextColor));

    std::string gridLineColor = CommonFunctions::GenerateDarkerColor(backgroundColor, 30 * (theme->isLight() ? 1 : -1));
    if (!chart->axes(Qt::Vertical).empty()) {
        auto verticalAxis = chart->axes(Qt::Vertical)[0];
        verticalAxis->setGridLinePen(CommonFunctions::GetQColorFromString(gridLineColor));
        verticalAxis->setLinePen(CommonFunctions::GetQColorFromString(CommonFunctions::GetContrastingTextColor(widgetBackgroundColor)));
        verticalAxis->setLabelsBrush(CommonFunctions::GetQColorFromString(bodyTextColor));
    }
    if (!chart->axes(Qt::Horizontal).empty()) {
        auto horizontalAxis = chart->axes(Qt::Horizontal)[0];
        horizontalAxis->setGridLinePen(CommonFunctions::GetQColorFromString(gridLineColor));
        horizontalAxis->setLinePen(CommonFunctions::GetQColorFromString(CommonFunctions::GetContrastingTextColor(widgetBackgroundColor)));
        horizontalAxis->setLabelsBrush(CommonFunctions::GetQColorFromString(bodyTextColor));
    }
    char buf[400];
    sprintf(buf, "QWidget#%s{ background: %s; color: %s }",
            pauseButton->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            titleTextColor.c_str()
    );
    pauseButton->setStyleSheet(buf);
    memset(buf,0,strlen(buf));
    sprintf(buf, "QWidget#%s{ background: %s; color: %s }",
            resetButton->objectName().toStdString().c_str(),
            backgroundColor.c_str(),
            titleTextColor.c_str()
    );
    resetButton->setStyleSheet(buf);
}

void RobotGui::LivePlotWidget::generateGraph() {
    if(pauseState) { return; }
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
    for (const auto& line: lineConfig->lines) {
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
    for (auto line: lineConfig->lines) {
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
    if(maxSpeed) { return true; }
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


