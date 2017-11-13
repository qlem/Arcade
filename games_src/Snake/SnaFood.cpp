//
// Created by pierre on 21/03/17.
//

#include "SnaFood.hpp"

arcade::SnaFood::SnaFood(int x, int y) : _value(Value::FOOD) {
    _positon.set_x(x);
    _positon.set_y(y);
}

arcade::SnaFood::SnaFood() {}

arcade::SnaFood::~SnaFood() {}

const arcade::SnaPos &arcade::SnaFood::get_positon() const {
    return _positon;
}

void arcade::SnaFood::set_positon(int x, int y) {
    SnaPos pos(x, y);
    SnaFood::_positon = pos;
}

const arcade::Value &arcade::SnaFood::get_value() const {
    return _value;
}

void arcade::SnaFood::set_value(arcade::Value _value) {
    SnaFood::_value = _value;
}


