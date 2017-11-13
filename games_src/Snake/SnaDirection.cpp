//
// Created by pierre on 14/03/17.
//

#include "SnaDirection.hpp"

arcade::SnaDirection::SnaDirection() : _currentDir(Axis::LEFT), _newDir(Axis::LEFT) {}

arcade::SnaDirection::~SnaDirection() {

}

arcade::SnaDirection::Axis arcade::SnaDirection::get_currentDir() const {
    return _currentDir;
}

void arcade::SnaDirection::set_currentDir(arcade::SnaDirection::Axis _direction) {
    SnaDirection::_currentDir = _direction;
}

arcade::SnaDirection::Axis arcade::SnaDirection::get_newDir() const {
    return _newDir;
}

void arcade::SnaDirection::set_newDir(arcade::SnaDirection::Axis _direction) {
    SnaDirection::_newDir = _direction;
}

