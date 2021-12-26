#include <iostream>
#include "BaseWidget.h"

BaseWidget::BaseWidget(QWidget *_parent_, const RobotGui::WidgetConfig_ptr& _configInfo, WidgetData *_widgetData) : staticPos(_configInfo->staticPos), QWidget(_parent_) {
    configInfo = _configInfo;
    widgetData = _widgetData;
    _parent = _parent_;
    currentTheme = Light;
    configInfo->draggable = !staticPos && _configInfo->draggable;
    this->setObjectName(QString::fromStdString(_configInfo->objectName));
    // Set up the right click menu
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showContextMenu(QPoint)));
    // Initialize position
    move(configInfo->x, configInfo->y);
}

void BaseWidget::setPosition(int _x, int _y) {
    if(!staticPos) {
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

void BaseWidget::updateData(bool focus) {
    updateData(focus ? _parent : nullptr);
}

void BaseWidget::updateData(QWidget *activeParent) {
    if(activeParent == _parent) {
        if(!inFocusLast) {
            inFocusLast = true;
            updateOnInFocus();
        }
        updateInFocus();
    } else {
        inFocusLast = false;
        updateNoFocus();
    }
}

void BaseWidget::setDraggability(bool _draggable) {
    configInfo->draggable = !staticPos && _draggable;
    customUpdateDraggability(_draggable);
}

void BaseWidget::toggleDraggability() {
    if(!staticPos) {
        configInfo->draggable = !configInfo->draggable;
    }
}

void BaseWidget::mousePressEvent(QMouseEvent *event) {
    if(!staticPos && configInfo->draggable) {
        clicked = true;
        startX = event->globalX();
        startY = event->globalY();
        startWX = configInfo->x;
        startWY = configInfo->y;
    }
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event) {
    if(!staticPos) {
        clicked = false;
        startX = event->globalX();
        startY = event->globalY();
    }
}

void BaseWidget::mouseMoveEvent(QMouseEvent *event) {
    if(!staticPos && clicked && configInfo->draggable) {
        setPosition(event->globalX() - startX + startWX, event->globalY() - startY + startWY );
    }
}

// Style
void BaseWidget::updateStyle(Themes _theme, bool overwrite) {
    currentTheme = _theme;
    customUpdateStyle(overwrite);
    updateChildrenStyle(overwrite);
}

void BaseWidget::setBackgroundColor(QAction *channelAction) {
    configInfo->backgroundColor = channelAction->data().toString().toStdString();
    customUpdateStyle(false);
}

void BaseWidget::setTextColor(QAction *channelAction) {
    configInfo->textColor = channelAction->data().toString().toStdString();
    customUpdateStyle(false);
}

void BaseWidget::showContextMenu(const QPoint &pos) {
    std::vector<QMenu*> menus;
    auto contextMenu = new QMenu(this);
    menus.emplace_back(contextMenu);
    contextMenu->setObjectName(CONTEXT_MENU_NAME);
    if(!staticPos) {
        contextMenu->addAction("Toggle Draggability", this, SLOT(toggleDraggability()));
    }
    if(styledBackground || styledWidgetBackgroundColor) {
        auto *backgroundColor = contextMenu->addMenu("Background color");
        menus.emplace_back(backgroundColor);
        backgroundColor->setObjectName(QString(CONTEXT_MENU_NAME) + "BGColor");
        const char *colors[] = { "theme", "none", "black", "white", "grey", "green", "blue", "red", "orange", "yellow" };
        for(auto & color : colors) {
            if(std::strcmp("none", color) != 0 || styledSeeThroughBackground) {
                auto *sub1 = backgroundColor->addAction(color);
                sub1->setData(color);
            }
        }
        connect(backgroundColor, SIGNAL(triggered(QAction*)), this, SLOT(setBackgroundColor(QAction*)));
    }
    if(styledText) {
        auto *textColor = contextMenu->addMenu("Text color");
        menus.emplace_back(textColor);
        textColor->setObjectName(QString(CONTEXT_MENU_NAME) + "TXTColor");
        const char *colors[] = { "theme", "black", "white", "grey", "green", "blue", "red", "orange", "yellow" };
        for(auto & color : colors) {
            auto *sub1 = textColor->addAction(color);
            sub1->setData(color);
        }
        connect(textColor, SIGNAL(triggered(QAction*)), this, SLOT(setTextColor(QAction*)));
    }

    Themes theme = Dark;
    for(auto & element : menus) {
        QString style =
                "QMenu#" + element->objectName() + "{"
                                                   "background-color : " + QString::fromStdString(Theme2::getRightClickMenuBackgroundColorStr(theme)) +
                "; color : " + QString::fromStdString(Theme2::getTextColorStr(theme)) +
                "}" + "QMenu::item:selected#" + element->objectName() + "{"
                                                                        "background-color :" + QString::fromStdString(Theme2::getRightClickMenuHighlightColorStr(theme)) +
                "}";
        element->setStyleSheet(style);
    }
    contextMenu->exec(mapToGlobal(pos));
}

void BaseWidget::customUpdateStyle(bool overwrite){}
void BaseWidget::updateChildrenStyle(bool overwrite) {}

void BaseWidget::updateInFocus() {}
void BaseWidget::updateNoFocus() {}
void BaseWidget::updateOnInFocus() {}
void BaseWidget::customUpdate() {}

void BaseWidget::customUpdateDraggability(bool _draggable) {}


