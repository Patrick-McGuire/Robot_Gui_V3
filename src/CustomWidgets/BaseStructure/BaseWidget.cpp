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

RobotGui::BaseWidget::BaseWidget(QWidget *_parent_, const RobotGui::WidgetBaseConfig::SharedPtr &_configInfo, RobotGui::WidgetData *_widgetData, RobotGui::Theme *_theme) : QWidget(_parent_) {
    _configInfo->require(WidgetConstants::BACKGROUND_COLOR);
    _configInfo->require(WidgetConstants::TEXT_COLOR);
    _configInfo->require(WidgetConstants::HEADER_COLOR);
    _configInfo->require(WidgetConstants::RELIEF);
    _configInfo->require(WidgetConstants::FONT);
    _configInfo->require(WidgetConstants::FOREGROUND_COLOR);
    _configInfo->require(WidgetConstants::BORDER_COLOR);

    configInfo = _configInfo;
    widgetData = _widgetData;
    _parent = _parent_;
    theme = _theme;
    configInfo->draggable = !configInfo->staticPos && _configInfo->draggable;
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

    connect(configInfo.get(), SIGNAL(configChanged()), this, SLOT(updateFromConfigInfo()));
}

RobotGui::BaseWidget::~BaseWidget() {
    delete widgetSettingsDialog;
}

void RobotGui::BaseWidget::setPosition(int _x, int _y) {
    if (!configInfo->staticPos) {
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
    configInfo->draggable = !configInfo->staticPos && _draggable;
    customUpdateDraggability(_draggable);
}

void RobotGui::BaseWidget::toggleDraggability() {
    if (!configInfo->staticPos) {
        configInfo->draggable = !configInfo->draggable;
    }
}

void RobotGui::BaseWidget::paintEvent(QPaintEvent *_event) {
    QPainter painter(this);
    if (configInfo->borderColor.is_initialized()) {
        painter.setPen(CommonFunctions::GetQColorFromString(getBorderColor()));
        if (configInfo->backgroundColor.is_initialized() && configInfo->backgroundColor.get() != RobotGui::TRANSPARENT_STYLE) {
            painter.setBrush(CommonFunctions::GetQColorFromString(getWidgetBackgroundColor()));
        }
        painter.drawRect(0, 0, width() - 1, height() - 1);
    }
}

void RobotGui::BaseWidget::mousePressEvent(QMouseEvent *event) {
    if (!configInfo->staticPos && configInfo->draggable) {
        clicked = true;
        startX = event->globalX();
        startY = event->globalY();
        startWX = configInfo->x;
        startWY = configInfo->y;
    }
}

void RobotGui::BaseWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (!configInfo->staticPos) {
        clicked = false;
        startX = event->globalX();
        startY = event->globalY();
    }
}

void RobotGui::BaseWidget::mouseMoveEvent(QMouseEvent *event) {
    if (!configInfo->staticPos && clicked && configInfo->draggable) {
        setPosition(event->globalX() - startX + startWX, event->globalY() - startY + startWY);
    }
}

std::string RobotGui::BaseWidget::getBackgroundColor() {
    if (configInfo->backgroundColor.is_initialized()) {
        if (configInfo->backgroundColor.get() == RobotGui::Xml::NONE_CONST) {
            return RobotGui::TRANSPARENT_STYLE;
        } else if (configInfo->backgroundColor.get() != RobotGui::Xml::THEME_CONST) {
            return configInfo->backgroundColor.get();
        }
    }
    return theme->getBackgroundColor();
}

std::string RobotGui::BaseWidget::getWidgetBackgroundColor() {
    if (configInfo->backgroundColor.is_initialized()) {
        if (configInfo->backgroundColor.get() == RobotGui::Xml::NONE_CONST) {
            return RobotGui::TRANSPARENT_STYLE;
        } else if (configInfo->backgroundColor.get() != RobotGui::Xml::THEME_CONST) {
            return configInfo->backgroundColor.get();
        }
    }
    return theme->getWidgetBackgroundColor();
}

std::string RobotGui::BaseWidget::getTextColor() {
    if (configInfo->textColor.is_initialized()) {
        if (configInfo->textColor.get() == RobotGui::Xml::NONE_CONST) {
            return RobotGui::TRANSPARENT_STYLE;
        } else if (configInfo->textColor.get() != RobotGui::Xml::THEME_CONST) {
            return configInfo->textColor.get();
        }
    }
    return theme->getTextColor();
}

std::string RobotGui::BaseWidget::getHeaderColor() {
    if (configInfo->headerColor.is_initialized()) {
        if (configInfo->headerColor.get() == RobotGui::Xml::NONE_CONST) {
            return RobotGui::TRANSPARENT_STYLE;
        } else if (configInfo->headerColor.get() != RobotGui::Xml::THEME_CONST) {
            return configInfo->headerColor.get();
        }
    }
    return theme->getHeaderColor();
}

std::string RobotGui::BaseWidget::getBorderColor() {
    if (configInfo->borderColor.is_initialized()) {
        if (configInfo->borderColor.get() == RobotGui::Xml::NONE_CONST) {
            return RobotGui::TRANSPARENT_STYLE;
        } else if (configInfo->borderColor.get() != RobotGui::Xml::THEME_CONST) {
            return configInfo->borderColor.get();
        }
    }
    return theme->getBorderColor();
}

void RobotGui::BaseWidget::updateStyle() {
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
    contextMenu->addAction("Edit", configInfo.get(), SLOT(showEditMenu()));
    if (!configInfo->staticPos) {
        contextMenu->addAction("Toggle Draggability", this, SLOT(toggleDraggability()));
    }
    if (configInfo->isRequired(WidgetConstants::BACKGROUND_COLOR)) {
        auto *backgroundColor = contextMenu->addMenu("Background color");
        menus.emplace_back(backgroundColor);
        backgroundColor->setObjectName(QString(CONTEXT_MENU_NAME) + "BGColor");
        const char *colors[] = {"theme", "none", "black", "white", "grey", "green", "blue", "red", "orange", "yellow"};
        for (auto &color: colors) {
//            if (std::strcmp("none", color) != 0 || styledSeeThroughBackground) {
            auto *sub1 = backgroundColor->addAction(color);
            sub1->setData(color);
//            }
        }
        connect(backgroundColor, SIGNAL(triggered(QAction * )), this, SLOT(setBackgroundColor(QAction * )));
    }
    if (configInfo->isRequired(WidgetConstants::TEXT_COLOR)) {
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
    repaint();
    setPosition(configInfo->x, configInfo->y);
}

void RobotGui::BaseWidget::customUpdateFromConfigInfo() {}


