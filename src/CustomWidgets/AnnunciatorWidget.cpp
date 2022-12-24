#include "AnnunciatorWidget.h"
#include "../WidgetData.h"
#include "../InternalJson.h"
#include "../Theme.h"
#include "BaseStructure/BaseWidget.h"

#include <QLabel>
#include <QGridLayout>

RobotGui::AnnunciatorWidget::AnnunciatorWidget(QWidget *parent, const RobotGui::WidgetBaseConfig::SharedPtr &configInfo, RobotGui::WidgetData *widgetData, RobotGui::Theme *_theme) : RobotGui::BaseWidget(parent, configInfo, widgetData, _theme) {
    int rows = 10;
    int columns = 2;
    if (configInfo->rowNumber.is_initialized() && configInfo->rowNumber != 0) { rows = configInfo->rowNumber.get(); }
    if (configInfo->columnNumber.is_initialized() && configInfo->columnNumber != 0) { columns = configInfo->columnNumber.get(); }
    source = configInfo->source.is_initialized() ? configInfo->source.get() : "";

    titleWidget = new QLabel();
    titleWidget->setText(QString::fromStdString(configInfo->title.get()));
    titleWidget->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    titleWidget->show();
    auto *layout = new QGridLayout();
    layout->addWidget(titleWidget, 0, 0, 1, columns);
    setLayout(layout);

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

void RobotGui::AnnunciatorWidget::updateInFocus() {
    if (widgetData->keyUpdated(source)) {
        if (widgetData->getJson()->mapGet(source)->getType() == RobotGui::InternalJson::vector_t) {
            auto configData = widgetData->getJson()->mapGet(source);
            for (int i = 0; i < configData->vectorSize(); i++) {
                auto boxConfig = configData->vectorGet(i);
                if (boxConfig->vectorSize() == 3) {
                    std::string boxName = boxConfig->vectorGet(0)->getString();
                    int boxState = boxConfig->vectorGet(1)->getInt();
                    std::string description = boxConfig->vectorGet(2)->getString();

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

            for (int i = configData->vectorSize(); i < annunciatorWidgetVector.size(); i++) {
                annunciatorWidgetVector[i]->setText("");
                annunciatorWidgetVector[i]->setToolTip("");
                annunciatorWidgetVector[i]->setToolTipDuration(0);
                annunciatorWidgetVector[i]->setStyleSheet("background: green");
            }
        }
    }
}

void RobotGui::AnnunciatorWidget::customUpdateStyle() {
    titleWidget->setStyleSheet(QString::fromStdString("color: " + getHeaderColor()));
    titleWidget->setFont(font());
}
