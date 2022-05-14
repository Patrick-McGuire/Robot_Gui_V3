#ifndef ROBOT_GUI_V3_LINEENTRY_H
#define ROBOT_GUI_V3_LINEENTRY_H

#include "QObject"
#include "QDialog"
#include "QPushButton"
#include "QCheckBox"
#include "QLineEdit"
#include "QComboBox"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "../../../lib/CommonFunctions.h"
#include "LineConfig.h"

namespace RobotGui {

    class LineEntry : public QWidget {
    Q_OBJECT
    public:
        LineEntry() {
            horizontal = new QHBoxLayout();
            setLayout(horizontal);

            delBut = new QPushButton("-");
            delBut->setFixedWidth(25);
            label = new QLineEdit();
            label->setFixedWidth(75);
            source = new QLineEdit();
            source->setFixedWidth(75);
            color = new QLineEdit();
            color->setFixedWidth(75);
            type = new QLineEdit();
            type->setFixedWidth(75);
            min = new QLineEdit();
            min->setValidator(new QDoubleValidator(min) );
            min->setFixedWidth(75);
            max = new QLineEdit();
            max->setValidator(new QDoubleValidator(max) );
            max->setFixedWidth(75);

            horizontal->addWidget(delBut);
            horizontal->addWidget(label);
            horizontal->addWidget(source);
            horizontal->addWidget(color);
            horizontal->addWidget(type);
            horizontal->addWidget(min);
            horizontal->addWidget(max);

            connect(delBut, SIGNAL(clicked()), this, SIGNAL(deleted()));

            connect(label, SIGNAL(textEdited(QString)), this, SIGNAL(updated()));
            connect(source, SIGNAL(textEdited(QString)), this, SIGNAL(updated()));
            connect(color, SIGNAL(textEdited(QString)), this, SIGNAL(updated()));
            connect(type, SIGNAL(textEdited(QString)), this, SIGNAL(updated()));
            connect(min, SIGNAL(textEdited(QString)), this, SIGNAL(updated()));
            connect(max, SIGNAL(textEdited(QString)), this, SIGNAL(updated()));
        }

        void setLineInfo(std::string *_label, std::string *_source, boost::optional<std::string> *_color, boost::optional<std::string> *_type, boost::optional<double> *_min,
                         boost::optional<double> *_max) {
            label->setText(_label->c_str());
            source->setText(_source->c_str());
            if (_color->is_initialized()) { color->setText(_color->get().c_str()); }
            else { color->hide(); }
            if (_type->is_initialized()) { type->setText(_type->get().c_str()); }
            else { type->hide(); }
            if (_min->is_initialized()) { min->setText(std::to_string(_min->get()).c_str()); }
            else { min->hide(); }
            if (_max->is_initialized()) { max->setText(std::to_string(_max->get()).c_str()); }
            else { max->hide(); }
        }

        QHBoxLayout *horizontal;
        QPushButton *delBut;
        QLineEdit *label;
        QLineEdit *source;
        QLineEdit *color;
        QLineEdit *type;
        QLineEdit *min;
        QLineEdit *max;

    signals:

        void updated();

        void deleted();
    };
}

#endif //ROBOT_GUI_V3_LINEENTRY_H
