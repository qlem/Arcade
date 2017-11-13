//
// Created by pierre on 07/04/17.
//

#include "SolDirection.hpp"

arcade::SolDirection::SolDirection() {}

arcade::SolDirection::SolDirection(arcade::SolDirection::Axis _direction) :
        _currentDir(_direction),
        _newDir(_direction)
{}

arcade::SolDirection::~SolDirection() {

}

arcade::SolDirection::Axis arcade::SolDirection::get_currentDir() const {
    return _currentDir;
}

arcade::SolDirection::Axis arcade::SolDirection::get_newDir() const {
    return _newDir;
}

void arcade::SolDirection::set_currentDir(Axis _currentDir) {
    SolDirection::_currentDir = _currentDir;
}

void arcade::SolDirection::set_newDir(Axis _newDir) {
    SolDirection::_newDir = _newDir;
}
