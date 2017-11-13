//
// Created by pierre on 14/03/17.
//

#include "SnaPos.hpp"

arcade::SnaPos::SnaPos(int x, int y) : _x(x), _y(y) {}

arcade::SnaPos::SnaPos() {}

arcade::SnaPos::~SnaPos() {

}

int arcade::SnaPos::get_x() const {
    return _x;
}

int arcade::SnaPos::get_y() const {
    return _y;
}

void arcade::SnaPos::set_x(int _x) {
    SnaPos::_x = _x;
}

void arcade::SnaPos::set_y(int _y) {
    SnaPos::_y = _y;
}

