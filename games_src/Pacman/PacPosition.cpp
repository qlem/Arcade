//
// Created by dommer_c on 07/04/17.
//

#include "PacPosition.h"

int arcade::PacPosition::getX() {
    return this->_x;
}

int arcade::PacPosition::getY() {
    return this->_y;
}

void arcade::PacPosition::setX(int x) {
    this->_x = x;
}

void arcade::PacPosition::setY(int y) {
    this->_y = y;
}
