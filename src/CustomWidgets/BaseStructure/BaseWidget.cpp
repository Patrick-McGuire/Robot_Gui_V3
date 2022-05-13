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
#include "WidgetSettingsDialog.h"

RobotGui::BaseWidget::BaseWidget(QWidget *_parent_, const RobotGui::WidgetBaseConfig::SharedPtr &_configInfo, RobotGui::WidgetData *_widgetData, RobotGui::Theme *_theme) : staticPos(_configInfo->staticPos), QWidget(_parent_) {
    configInfo = _configInfo;
    widgetData = _widgetData;
    _parent = _parent_;
    theme = _theme;
    configInfo->draggable = !staticPos && _configInfo->draggable;
    this->setObjectName(QString::fromStdString(_configInfo->objectName));

    if (configInfo->font.is_initialized() && configInfo->font.get() != RobotGui::Xml::THEME_CONST) {
        int fontSize = configInfo->fontSize.is_initialized() ? configInfo->fontSize.get() : 12;
        setFont(QFont(QString::fromStdString(configInfo->font.get()), fontSize));
    }

    // Set up the right click menu
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    // Initialize position
    move(configInfo->x, configInfo->y);
    updateStyle();
}

RobotGui::BaseWidget::~BaseWidget() {
    delete widgetSettingsDialog;
}

void RobotGui::BaseWidget::setPosition(int _x, int _y) {
    if (!staticPos) {
        // Clip values to be inside the window
        if (_x > _parent->size().width() - this->width()) { _x = _parent->size().width() - this->width(); }
        if (_y > _parent->size().height() - this->height()) { _y = _parent->size().height() - this->height(); }
        if (_x < 0) { _x = 0; }
        if (_y < 0) { _y = 0; }
        configInfo->x = _x;
        configInfo->y = _y;
        // Move the widget on the screen
        move(_x, _y);
    }
}

void RobotGui::BaseWidget::updateData(bool focus) {
    updateData(focus ? _parent : nullptr);
}

void RobotGui::BaseWidget::updateData(QWidget *activeParent) {
    if (activeParent == _parent) {
        if (!inFocusLast) {
            inFocusLast = true;
            updateOnInFocus();
        }
        updateInFocus();
    } else {
        inFocusLast = false;
        updateNoFocus();
    }
}

void RobotGui::BaseWidget::setDraggability(bool _draggable) {
    configInfo->draggable = !staticPos && _draggable;
    customUpdateDraggability(_draggable);
}

void RobotGui::BaseWidget::toggleDraggability() {
    if (!staticPos) {
        configInfo->draggable = !configInfo->draggable;
    }
}

void RobotGui::BaseWidget::paintEvent(QPaintEvent *_event) {
    QPainter painter(this);
    if (drawBorder) {
        painter.setPen(CommonFunctions::GetQColorFromString(borderColor));
        if (backgroundColor != RobotGui::TRANSPARENT_STYLE) {
            painter.setBrush(CommonFunctions::GetQColorFromString(widgetBackgroundColor));
        }
        painter.drawRect(0, 0, width() - 1, height() - 1);
    }
}

void RobotGui::BaseWidget::mousePressEvent(QMouseEvent *event) {
    if (!staticPos && configInfo->draggable) {
        clicked = true;
        startX = event->globalX();
        startY = event->globalY();
        startWX = configInfo->x;
        startWY = configInfo->y;
    }
}

void RobotGui::BaseWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (!staticPos) {
        clicked = false;
        startX = event->globalX();
        startY = event->globalY();
    }
}

void RobotGui::BaseWidget::mouseMoveEvent(QMouseEvent *event) {
    if (!staticPos && clicked && configInfo->draggable) {
        setPosition(event->globalX() - startX + startWX, event->globalY() - startY + startWY);
    }
}

// Style
void RobotGui::BaseWidget::updateStyle() {
    backgroundColor = configInfo->backgroundColor.get();
    widgetBackgroundColor = configInfo->backgroundColor.get();
    bodyTextColor = configInfo->textColor.get();
    titleTextColor = configInfo->headerColor.get();
    borderColor = configInfo->borderColor.get();
    // Check background color
    if (backgroundColor == RobotGui::Xml::THEME_CONST) {
        backgroundColor = theme->getBackgroundColor();
    } else if (backgroundColor == RobotGui::Xml::NONE_CONST) {
        backgroundColor = RobotGui::TRANSPARENT_STYLE;
    }
    // Check widget background color
    if (widgetBackgroundColor == RobotGui::Xml::THEME_CONST) {
        widgetBackgroundColor = theme->getWidgetBackgroundColor();
    } else if (widgetBackgroundColor == RobotGui::Xml::NONE_CONST) {
        widgetBackgroundColor = RobotGui::TRANSPARENT_STYLE;
    }
    // Check body text
    if (bodyTextColor == RobotGui::Xml::THEME_CONST) {
        bodyTextColor = theme->getBodyTextColor();
    }
    // Check title text color
    if (titleTextColor == RobotGui::Xml::THEME_CONST) {
        titleTextColor = theme->getTitleTextColor();
    }
    // Check border color
    if (borderColor == RobotGui::Xml::THEME_CONST) {
        borderColor = theme->getBorderColor();
    } else if (borderColor == RobotGui::Xml::NONE_CONST) {
        borderColor = RobotGui::TRANSPARENT_STYLE;
    }
    customUpdateStyle();
    updateChildrenStyle();
}

void RobotGui::BaseWidget::setBackgroundColor(QAction *channelAction) {
    configInfo->backgroundColor = channelAction->data().toString().toStdString();
    updateStyle();
}

void RobotGui::BaseWidget::setTextColor(QAction *channelAction) {
    configInfo->textColor = channelAction->data().toString().toStdString();
    updateStyle();
}

void RobotGui::BaseWidget::showContextMenu(const QPoint &pos) {
    std::vector<QMenu *> menus;
    auto contextMenu = new QMenu(this);
    menus.emplace_back(contextMenu);
    contextMenu->setObjectName(CONTEXT_MENU_NAME);
    contextMenu->addAction("Edit", this, SLOT(showEditMenu()));
    if (!staticPos) {
        contextMenu->addAction("Toggle Draggability", this, SLOT(toggleDraggability()));
    }
    if (styledBackground || styledWidgetBackgroundColor) {
        auto *backgroundColor = contextMenu->addMenu("Background color");
        menus.emplace_back(backgroundColor);
        backgroundColor->setObjectName(QString(CONTEXT_MENU_NAME) + "BGColor");
        const char *colors[] = {"theme", "none", "black", "white", "grey", "green", "blue", "red", "orange", "yellow"};
        for (auto &color: colors) {
            if (std::strcmp("none", color) != 0 || styledSeeThroughBackground) {
                auto *sub1 = backgroundColor->addAction(color);
                sub1->setData(color);
            }
        }
        connect(backgroundColor, SIGNAL(triggered(QAction * )), this, SLOT(setBackgroundColor(QAction * )));
    }
    if (styledText) {
        auto *textColor = contextMenu->addMenu("Text color");
        menus.emplace_back(textColor);
        textColor->setObjectName(QString(CONTEXT_MENU_NAME) + "TXTColor");
        const char *colors[] = {"theme", "black", "white", "grey", "green", "blue", "red", "orange", "yellow"};
        for (auto &color: colors) {
            auto *sub1 = textColor->addAction(color);
            sub1->setData(color);
        }
        connect(textColor, SIGNAL(triggered(QAction * )), this, SLOT(setTextColor(QAction * )));
    }

    for (auto &element: menus) {
        QString style =
                "QMenu#" + element->objectName() + "{"
                                                   "background-color : " + QString::fromStdString(theme->getBackgroundColor()) +
                "; color : " + QString::fromStdString(CommonFunctions::GetContrastingTextColor(theme->getBackgroundColor())) +
                "}" + "QMenu::item:selected#" + element->objectName() + "{"
                                                                        "background-color :" + QString::fromStdString(theme->getHighlightColor()) +
                "}";
        element->setStyleSheet(style);
    }
    contextMenu->exec(mapToGlobal(pos));
}

void RobotGui::BaseWidget::showEditMenu() {
    if(widgetSettingsDialog == nullptr) {
        widgetSettingsDialog = new WidgetSettingsDialog(this, configInfo, widgetData, theme);
        connect(widgetSettingsDialog, SIGNAL(configChanged()), this, SLOT(updateFromConfigInfo()));
        widgetSettingsDialog->show();
    } else {
        widgetSettingsDialog->show();
    }
}

void RobotGui::BaseWidget::customUpdateStyle() {}

void RobotGui::BaseWidget::updateChildrenStyle() {}

void RobotGui::BaseWidget::updateInFocus() {}

void RobotGui::BaseWidget::updateNoFocus() {}

void RobotGui::BaseWidget::updateOnInFocus() {}

void RobotGui::BaseWidget::customUpdate() {}

void RobotGui::BaseWidget::customUpdateDraggability(bool _draggable) {}

RobotGui::WidgetBaseConfig::SharedPtr RobotGui::BaseWidget::getConfig() {
    return configInfo;
}

void RobotGui::BaseWidget::updateFromConfigInfo() {
    updateStyle();
    customUpdateFromConfigInfo();
}

void RobotGui::BaseWidget::customUpdateFromConfigInfo() {

}
