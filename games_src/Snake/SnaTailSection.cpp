//
// Created by pierre on 16/03/17.
//

#include "SnaTailSection.hpp"

arcade::SnaTailSection::SnaTailSection() :
        _positon(_positon),
        _value(Value::TAILSCT),
        _plump(false)
{}

arcade::SnaTailSection::SnaTailSection(int x, int y) :
        _positon(x, y),
        _value(Value::TAILSCT),
        _plump(false)
{}

arcade::SnaTailSection::~SnaTailSection() {}

const arcade::SnaPos &arcade::SnaTailSection::get_positon() const {
    return _positon;
}

const arcade::Value &arcade::SnaTailSection::get_value() const {
    return _value;
}

void arcade::SnaTailSection::set_positon(int x, int y) {
    SnaPos         position(x,y);
    SnaTailSection::_positon = position;
}

void arcade::SnaTailSection::set_value(arcade::Value _value) {
    SnaTailSection::_value = _value;
}

bool arcade::SnaTailSection::is_plump() const {
    return _plump;
}

void arcade::SnaTailSection::set_plump(bool _plump) {
    SnaTailSection::_plump = _plump;
}
