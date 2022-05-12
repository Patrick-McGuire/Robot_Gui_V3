#ifndef ROBOT_GUI_V3_WIDGETSETTINGSDIALOG_H
#define ROBOT_GUI_V3_WIDGETSETTINGSDIALOG_H
#include "QObject"
#include <iostream>
#include <QtGui/QPainter>
#include <QVBoxLayout>
#include <QAbstractButton>
#include <QLabel>
#include "BaseWidget.h"
#include "../../../lib/CommonFunctions.h"
#include "../../WidgetData.h"
#include "../../Theme.h"
#include "QDialog"
#include "QPushButton"
#include "QCheckBox"
#include "BaseWidget.h"
#include "QLineEdit"

namespace RobotGui {
    /**
     * @class WidgetSettings
     * Class that holds a bunch of different settings for widgets with getters and setters
     *
     * @author Patrick McGuire (Patrick-McGuire)
     */
    class BaseWidget;

    class WidgetSettingsDialog : public QDialog {
    Q_OBJECT
    public:
        WidgetSettingsDialog(BaseWidget *_widget, const WidgetBaseConfig::SharedPtr &_widgetConfigInfo, WidgetData *_widgetData, Theme *_theme);

    signals:
        void configChanged();

    private slots:
        void updateWidgetData();

    private:
        void closeEvent(QCloseEvent *bar);

        BaseWidget *widget;
        WidgetBaseConfig::SharedPtr widgetConfigInfo;
        WidgetData *widgetData;
        Theme *theme;

        // All default settings
        QCheckBox *draggableCheckbox;
        QLineEdit *titleSet;
    };

}
#endif //ROBOT_GUI_V3_WIDGETSETTINGSDIALOG_H
