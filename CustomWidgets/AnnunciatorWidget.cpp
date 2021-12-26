//
// Created by nathan on 12/26/21.
//

#include "AnnunciatorWidget.h"

#include <QLabel>
#include <QGridLayout>

AnnunciatorWidget::AnnunciatorWidget(QWidget *parent, const WidgetConfig_ptr &configInfo, WidgetData *widgetData) : BaseWidget(parent, configInfo, widgetData) {
    int rows = 10;
    int columns = 2;
    if (configInfo->rowNumber != 0) { rows = configInfo->rowNumber; }
    if (configInfo->columnNumber != 0) { columns = configInfo->columnNumber; }

    titleWidget = new QLabel();
    titleWidget->setText(QString::fromStdString(configInfo->title));
    titleWidget->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    titleWidget->show();
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(titleWidget, 0, 0, 1, columns);
    setLayout(layout);

    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            QLabel *box = new QLabel();
            box->setMaximumWidth(150);
            box->setMinimumWidth(150);
            box->setStyleSheet("background: green");
            layout->addWidget(box, j + 1, i);
            annunciatorWidgetVector.push_back(box);
        }
    }

    adjustSize();
}
