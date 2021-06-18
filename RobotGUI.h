#ifndef ROBOT_GUI_V3_ROBOTGUI_H
#define ROBOT_GUI_V3_ROBOTGUI_H
#include <QObject>
#include <QTimer>

class RobotGUI : public QObject {
Q_OBJECT
public:
    QTimer *timer;
    RobotGUI(QWidget *parent = nullptr);

public slots:
    void updateGUI();
};


#endif //ROBOT_GUI_V3_ROBOTGUI_H
