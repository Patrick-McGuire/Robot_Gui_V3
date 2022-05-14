#ifndef ROBOT_GUI_V3_WIDGETSETTINGSDIALOG_H
#define ROBOT_GUI_V3_WIDGETSETTINGSDIALOG_H

#include "QObject"
#include <iostream>
#include <QtGui/QPainter>
#include <QVBoxLayout>
#include <QAbstractButton>
#include <QLabel>
#include "../../../lib/CommonFunctions.h"
#include "WidgetBaseConfig.h"
#include "QDialog"
#include "QPushButton"
#include "QCheckBox"
#include "QLineEdit"
#include "QComboBox"
#include "ColorEntry.h"

namespace RobotGui {
    /**
     * @class WidgetSettings
     * Class that holds a bunch of different settings for widgets with getters and setters
     *
     * @author Patrick McGuire (Patrick-McGuire)
     */
    class WidgetBaseConfig;

    class WidgetSettingsDialog : public QDialog {
    Q_OBJECT
    public:

        WidgetSettingsDialog();

        void addEntry(const std::string &title, QWidget *wid);

        QLineEdit *addTextEntry(const std::string &title, const std::string &text);

        QLineEdit *addIntEntry(const std::string &title, int val);

        QLineEdit *addDoubleEntry(const std::string &title, double val);

        QCheckBox *addBoolEntry(const std::string &title, bool val);

        ColorEntry *addColorEntry(const std::string &title, const std::string &color);

    private:
        QGridLayout *dialogLayout;
        int nextRow = 0;

    };

}
#endif //ROBOT_GUI_V3_WIDGETSETTINGSDIALOG_H
