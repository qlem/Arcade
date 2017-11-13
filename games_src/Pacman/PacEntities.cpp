//
// Created by dommer_c on 07/04/17.
//

#include "PacEntities.h"

arcade::PacPosition arcade::PacEntities::getPosition(void) {
    return this->_position;
}

void arcade::PacEntities::moveUp() {
    this->_position.setY(this->_position.getY() - 1);
}

void arcade::PacEntities::moveDown() {
    this->_position.setY(this->_position.getY() + 1);
}

void arcade::PacEntities::moveLeft() {
    if (this->_position.getX() == 0)
        this->_position.setX(18);
    else
        this->_position.setX(this->_position.getX() - 1);
}

void arcade::PacEntities::moveRight() {
    if (this->_position.getX() == 18)
        this->_position.setX(0);
    else
        this->_position.setX(this->_position.getX() + 1);
}

arcade::PacEntities::PacEntities(int x, int y, Condition state, double velocity, isAlive isAlive) {
    this->_position.setX(x);
    this->_position.setY(y);
    this->_condition = state;
    this->_velocity = velocity;
    this->_distance = 0.0;
    this->_isAlive = isAlive;
}

arcade::PacEntities::Condition arcade::PacEntities::getCondition(void) {
    return this->_condition;
}

void arcade::PacEntities::setCondition(Condition condition) {
    this->_condition = condition;
}

void arcade::PacEntities::setNewDirection(arcade::PacDirection::eDirection direction) {
    this->_direction.setNewDirection(direction);
}

void arcade::PacEntities::setCurrentDirection(arcade::PacDirection::eDirection direction) {
    this->_direction.setCurrentDirection(direction);
}

arcade::PacDirection arcade::PacEntities::getDirection() {
    return this->_direction;
}

double arcade::PacEntities::getVelocity() const {
    return this->_velocity;
}

void arcade::PacEntities::setVelocity(double _velocity) {
    PacEntities::_velocity = _velocity;
}

double arcade::PacEntities::getDistance() const {
    return this->_distance;
}

void arcade::PacEntities::setDistance(double _distance) {
    PacEntities::_distance = _distance;
}

double arcade::PacEntities::getHarmlessDuration() {
    double i = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->_harmlessDuration).count();
    return i / 1000;
}

void arcade::PacEntities::resetHarmlessDuration() {
    this->_harmlessDuration = std::chrono::high_resolution_clock::now();
}

arcade::PacEntities::PacEntities() {

}

void arcade::PacEntities::setIsAlive(arcade::PacEntities::isAlive state) {
    this->_isAlive = state;
}

arcade::PacEntities::isAlive arcade::PacEntities::getIsAlive(void) {
    return this->_isAlive;
}
