//
// Created by pierre on 07/04/17.
//

#include "SolEntity.hpp"

arcade::SolEntity::SolEntity()
{}

arcade::SolEntity::SolEntity(int x, int y, SolDirection::Axis _currentDir, double _velocity) :
        _position(x, y),
        _direction(_currentDir),
        _velocity(_velocity),
        _distance(0.0)
{}

arcade::SolEntity::~SolEntity() {}

const arcade::SolPos &arcade::SolEntity::get_positon() const {
    return _position;
}

void arcade::SolEntity::set_positon(int x, int y) {
    _position.set_x(x);
    _position.set_y(y);
}

double arcade::SolEntity::get_velocity() const {
    return _velocity;
}

void arcade::SolEntity::set_velocity(double velocity) {
    _velocity = velocity;
}

void arcade::SolEntity::set_distance(double distance) {
    _distance = distance;
}

double arcade::SolEntity::get_distance() const {
    return _distance;
}

const arcade::SolDirection &arcade::SolEntity::get_direction() const {
    return _direction;
}

void arcade::SolEntity::moveUp() {
    _position.set_y(_position.get_y() - 1);
}

void arcade::SolEntity::moveDown() {
    _position.set_y(_position.get_y() + 1);
}

void arcade::SolEntity::moveRight() {
    _position.set_x(_position.get_x() + 1);
}

void arcade::SolEntity::moveLeft() {
    _position.set_x(_position.get_x() - 1);
}

void arcade::SolEntity::set_newDirection(arcade::SolDirection::Axis direction) {
    _direction.set_newDir(direction);
}

void arcade::SolEntity::set_currentDirection(arcade::SolDirection::Axis direction) {
    _direction.set_currentDir(direction);
}


