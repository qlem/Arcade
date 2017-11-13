//
// Created by pierre on 10/03/17.
//

#include <iostream>
#include "SnaPlayer.hpp"

arcade::SnaPlayer::SnaPlayer() : _positon(_positon), _value(Value::HEAD) {}
arcade::SnaPlayer::~SnaPlayer() {

}

const arcade::SnaPos &arcade::SnaPlayer::get_positon() const {
    return _positon;
}

const arcade::Value &arcade::SnaPlayer::get_value() const {
    return _value;
}

void arcade::SnaPlayer::set_positon(int x, int y) {
    SnaPos         position(x,y);
    SnaPlayer::_positon = position;
}

void arcade::SnaPlayer::set_value(arcade::Value _value) {
    SnaPlayer::_value = _value;
}

