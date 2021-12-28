#include "AnnunciatorWidget.h"

#include <QLabel>
#include <QGridLayout>

AnnunciatorWidget::AnnunciatorWidget(QWidget *parent, const RobotGui::WidgetConfig_ptr &configInfo, WidgetData *widgetData, Theme *_theme) : BaseWidget(parent, configInfo, widgetData, _theme) {
    int rows = 10;
    int columns = 2;
    if (configInfo->rowNumber != 0) { rows = configInfo->rowNumber; }
    if (configInfo->columnNumber != 0) { columns = configInfo->columnNumber; }
    source = configInfo->source;

    titleWidget = new QLabel();
    titleWidget->setText(QString::fromStdString(configInfo->title));
    titleWidget->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    titleWidget->show();
    auto *layout = new QGridLayout();
    layout->addWidget(titleWidget, 0, 0, 1, columns);
    setLayout(layout);
    configurablePos = true;

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            auto *box = new QLabel();
            box->setMaximumWidth(150);
            box->setMinimumWidth(150);
            box->setStyleSheet("background: green");
            layout->addWidget(box, j + 1, i);
            annunciatorWidgetVector.push_back(box);
        }
    }

    adjustSize();
}

void AnnunciatorWidget::updateInFocus() {
    if (widgetData->keyUpdated(source)) {
        if (widgetData->getKeyType(source) == WidgetData::vector_t) {
            auto configData = widgetData->getJSON(source);
            for (int i = 0; i < configData->vector.size(); i++) {
                auto boxConfig = configData->vector[i];
                if (boxConfig->vector.size() == 3) {
                    std::string boxName = boxConfig->vector[0]->stringVal;
                    int boxState = boxConfig->vector[1]->intVal;
                    std::string description = boxConfig->vector[2]->stringVal;

                    if (i < annunciatorWidgetVector.size()) {
                        annunciatorWidgetVector[i]->setText(QString::fromStdString(boxName));
                        annunciatorWidgetVector[i]->setToolTip(QString::fromStdString(description));
                        annunciatorWidgetVector[i]->setToolTipDuration(5000);

                        switch (boxState) {
                            case 0:
                                annunciatorWidgetVector[i]->setStyleSheet("background: green; color: black");
                                break;
                            case 1:
                                annunciatorWidgetVector[i]->setStyleSheet("background: yellow; color: black");
                                break;
                            case 2:
                                annunciatorWidgetVector[i]->setStyleSheet("background: red; color: black");
                                break;
                            default:
                                annunciatorWidgetVector[i]->setStyleSheet("background: blue; color: black");
                                break;
                        }
                    }
                }
            }
        }
    }
}

void AnnunciatorWidget::customUpdateStyle() {
    titleWidget->setStyleSheet(QString::fromStdString("color: " + titleTextColor));
    titleWidget->setFont(font());
}
