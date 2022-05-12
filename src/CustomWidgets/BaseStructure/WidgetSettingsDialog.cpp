#include "WidgetSettingsDialog.h"


RobotGui::WidgetSettingsDialog::WidgetSettingsDialog(BaseWidget *_widget,
                                                     const RobotGui::WidgetBaseConfig::SharedPtr &_widgetConfigInfo,
                                                     RobotGui::WidgetData *_widgetData,
                                                     RobotGui::Theme *_theme) : QDialog() {
    // Save members
    widget = _widget;
    widgetConfigInfo = _widgetConfigInfo;
    widgetData = _widgetData;
    theme = _theme;

    // Stuff needed to go inside the settings thing
    auto *dialogLayout = new QGridLayout;
    this->setLayout(dialogLayout);
    int nextRow = 0;

    // Draggable checkbox
    auto draggableLabel = new QLabel("Draggable:");
    draggableCheckbox = new QCheckBox();
    dialogLayout->addWidget(draggableLabel, nextRow, 0);
    dialogLayout->addWidget(draggableCheckbox, nextRow, 1);
    nextRow++;
    if(widget->staticPos) {
        draggableLabel->hide();
        draggableCheckbox->hide();
    } else {
        if(widgetConfigInfo->draggable) { draggableCheckbox->toggle(); }
        connect(draggableCheckbox, SIGNAL(clicked()), this, SLOT(updateWidgetData()));
    }

    // Title set
    auto titleSetLabel = new QLabel("Title:");
    titleSet = new QLineEdit();
    dialogLayout->addWidget(titleSetLabel, nextRow, 0);
    dialogLayout->addWidget(titleSet, nextRow, 1);
    nextRow++;
    if(widget->getConfig()->title.is_initialized()) {
        titleSet->setText(widgetConfigInfo->title->c_str());
        connect(titleSet, SIGNAL(textEdited(QString)), this, SLOT(updateWidgetData()));
    } else {
        titleSet->hide();
        titleSetLabel->hide();
    }

}

void RobotGui::WidgetSettingsDialog::updateWidgetData() {
    if(!widget->staticPos) {
        widgetConfigInfo->draggable = draggableCheckbox->isChecked();
    }
    if(widget->getConfig()->title.is_initialized()) {
        widgetConfigInfo->title = titleSet->text().toStdString();
    }
    emit configChanged();
}

void RobotGui::WidgetSettingsDialog::closeEvent(QCloseEvent *bar) {
    hide();
}

