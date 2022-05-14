#ifndef ROBOT_GUI_V3_COLORENTRY_H
#define ROBOT_GUI_V3_COLORENTRY_H
#include "QObject"
#include "QDialog"
#include "QPushButton"
#include "QCheckBox"
#include "QLineEdit"
#include "QComboBox"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "../../../lib/CommonFunctions.h"

namespace RobotGui {

    class ColorEntry : public QWidget {
    Q_OBJECT
    public:
        ColorEntry() {
            colors = QStringList({"custom", "theme", "none", "black", "white", "grey", "green", "blue", "red", "orange", "yellow"});
            horizontal = new QHBoxLayout();
            vertical = new QVBoxLayout();
            dropDown = new QComboBox();
            dropDown->addItems(colors);
            r = new QLineEdit();
            r->setFixedWidth(50);
            r->setValidator(new QIntValidator(r) );
            g = new QLineEdit();
            g->setFixedWidth(50);
            g->setValidator(new QIntValidator(g) );
            b = new QLineEdit();
            b->setFixedWidth(50);
            b->setValidator(new QIntValidator(b) );
            horizontal->addWidget(r);
            horizontal->addWidget(g);
            horizontal->addWidget(b);

            vertical->addWidget(dropDown);
            vertical->addItem(horizontal);

            connect(dropDown, SIGNAL(currentTextChanged(QString)), this, SIGNAL(updated()));
            connect(r, SIGNAL(textEdited(QString)), this, SIGNAL(updated()));
            connect(g, SIGNAL(textEdited(QString)), this, SIGNAL(updated()));
            connect(b, SIGNAL(textEdited(QString)), this, SIGNAL(updated()));
            setLayout(vertical);
        }

        QStringList colors;
        QHBoxLayout *horizontal;
        QVBoxLayout *vertical;
        QComboBox *dropDown;
        QLineEdit *r;
        QLineEdit *g;
        QLineEdit *b;

        std::string getColor() {
            if(dropDown->currentIndex() > 0) {
                return colors[dropDown->currentIndex()].toStdString();
            }
            return "rgb(" + r->text().toStdString() + "," + g->text().toStdString() + "," + b->text().toStdString() + ")";
        }

        void setColor(const std::string& color) {
            int index = colors.indexOf(color.c_str());
            if ( index > 0 ) {
                dropDown->setCurrentIndex(index);
            } else {
                dropDown->setCurrentIndex(0);
                auto rgb = CommonFunctions::GetRGBFromString(color);
                r->setText(QString(rgb[0]));
                g->setText(QString(rgb[1]));
                b->setText(QString(rgb[2]));
            }
        }

    signals:

        void updated();
    };
}

#endif //ROBOT_GUI_V3_COLORENTRY_H
