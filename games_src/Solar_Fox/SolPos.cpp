//
// Created by pierre on 14/03/17.
//

#include "SolPos.hpp"

arcade::SolPos::SolPos(int x, int y) : _x(x), _y(y) {}

arcade::SolPos::SolPos() {}

arcade::SolPos::~SolPos() {

}

int arcade::SolPos::get_x() const {
    return _x;
}

int arcade::SolPos::get_y() const {
    return _y;
}

void arcade::SolPos::set_x(int _x) {
    SolPos::_x = _x;
}

void arcade::SolPos::set_y(int _y) {
    SolPos::_y = _y;
}

