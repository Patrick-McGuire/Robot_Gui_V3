#include "TextBoxWidget.h"
#include <utility>

TextBoxWidget::TextBoxWidget(QWidget *parent, std::string name, int x, int y) : BaseWidget(parent, std::move(name), x, y) {
    this->setLayout(&layout);
    layout.addWidget(&titleBox);
    layout.addWidget(&textBox);

    textBox.setText("This123");
}