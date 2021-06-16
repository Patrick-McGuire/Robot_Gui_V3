#include "GUIMaker.h"
#include <iostream>

GUIMaker::GUIMaker(int thing) {
    m_abc = thing;
}

int GUIMaker::getABC() const {
//    return m_abc;
    std::cout << "SDF";
}

void GUIMaker::setABC(int abc) {
    m_abc = abc;
}

