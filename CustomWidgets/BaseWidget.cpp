#include <iostream>
#include "BaseWidget.h"

BaseWidget::BaseWidget(QWidget *parent, const WidgetConfig_ptr& configInfo, WidgetData *widgetData) : staticPos(configInfo->staticPos), QWidget(parent) {
    _configInfo = configInfo;
    _widgetData = widgetData;
    _parent = parent;
    currentTheme = Light;
    _configInfo->draggable = !staticPos && configInfo->draggable;
    this->setObjectName(QString::fromStdString(configInfo->objectName));
    // Set up the right click menu
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showContextMenu(QPoint)));
    // Initialize position
    move(_configInfo->x, _configInfo->y);
}

void BaseWidget::setPosition(int _x, int _y) {
    if(!staticPos) {
        // Clip values to be inside the window
        if (_x > _parent->size().width() - this->width()) { _x = _parent->size().width() - this->width(); }
        if (_y > _parent->size().height() - this->height()) { _y = _parent->size().height() - this->height(); }
        if (_x < 0) { _x = 0; }
        if (_y < 0) { _y = 0; }
        _configInfo->x = _x;
        _configInfo->y = _y;
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
    _configInfo->draggable = !staticPos && _draggable;
    customUpdateDraggability(_draggable);
}

void BaseWidget::toggleDraggability() {
    if(!staticPos) {
        _configInfo->draggable = !_configInfo->draggable;
    }
}

void BaseWidget::showContextMenu(const QPoint &pos) {
    std::vector<QMenu*> menus;
    auto contextMenu = new QMenu(this);
    menus.emplace_back(contextMenu);
    contextMenu->setObjectName(contextMenuName);
    if(!staticPos) {
        contextMenu->addAction("Toggle Draggability", this, SLOT(toggleDraggability()));
    }
    if(styledBackground || styledWidgetBackgroundColor) {
        auto *backgroundColor = contextMenu->addMenu("Background color");
        menus.emplace_back(backgroundColor);
        backgroundColor->setObjectName(QString(contextMenuName) + "BGColor");
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
        textColor->setObjectName(QString(contextMenuName) + "TXTColor");
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
                    "background-color : " + QString::fromStdString(Theme::getRightClickMenuBackgroundColorStr(theme)) +
                "; color : " + QString::fromStdString(Theme::getTextColorStr(theme)) +
                "}" + "QMenu::item:selected#" + element->objectName() + "{"
                    "background-color :" + QString::fromStdString(Theme::getRightClickMenuHighlightColorStr(theme)) +
                "}";
        element->setStyleSheet(style);
    }
    contextMenu->exec(mapToGlobal(pos));
}

void BaseWidget::mousePressEvent(QMouseEvent *event) {
    if(!staticPos && _configInfo->draggable) {
        clicked = true;
        startX = event->globalX();
        startY = event->globalY();
        startWX = _configInfo->x;
        startWY = _configInfo->y;
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
    if(!staticPos && clicked && _configInfo->draggable) {
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
    _configInfo->backgroundColor = channelAction->data().toString().toStdString();
    customUpdateStyle(false);
}

void BaseWidget::setTextColor(QAction *channelAction) {
    _configInfo->textColor = channelAction->data().toString().toStdString();
    customUpdateStyle(false);
}

void BaseWidget::customUpdateStyle(bool overwrite){}
void BaseWidget::updateChildrenStyle(bool overwrite) {}

void BaseWidget::updateInFocus() {}
void BaseWidget::updateNoFocus() {}
void BaseWidget::updateOnInFocus() {}
void BaseWidget::customUpdate() {}

void BaseWidget::customUpdateDraggability(bool _draggable) {}


