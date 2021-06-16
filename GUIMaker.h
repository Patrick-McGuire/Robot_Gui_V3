#ifndef ROBOT_GUI_V3_GUIMAKER_H
#define ROBOT_GUI_V3_GUIMAKER_H


class GUIMaker {
private:
    int m_abc;

public:
    GUIMaker(int thing);
    void setABC(int abc);
    int getABC() const;
};


#endif //ROBOT_GUI_V3_GUIMAKER_H
