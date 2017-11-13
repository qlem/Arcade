//
// Created by dommer_c on 07/04/17.
//

#include "PacDirection.h"

void arcade::PacDirection::setCurrentDirection(arcade::PacDirection::eDirection direction) {
    this->_currentDirection = direction;
}

arcade::PacDirection::eDirection arcade::PacDirection::getCurrentDirection(void) {
    return this->_currentDirection;
}

arcade::PacDirection::PacDirection() {
    this->_currentDirection = arcade::PacDirection::eDirection::STOP;
    this->_newDirection = arcade::PacDirection::eDirection::STOP;
}

void arcade::PacDirection::setNewDirection(arcade::PacDirection::eDirection direction) {
    this->_newDirection = direction;
}

arcade::PacDirection::eDirection arcade::PacDirection::getNewDirection(void) {
    return this->_newDirection;
}
