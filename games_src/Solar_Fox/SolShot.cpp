//
// Created by pierre on 08/04/17.
//

#include "SolShot.hpp"

arcade::SolShot::SolShot(int x, int y, SolDirection::Axis _currentDir, double _velocity,
                   int _distRemaining, arcade::SolShot::Type _type) :
        SolEntity(x, y, _currentDir, _velocity),
        _distRemaining(_distRemaining),
        _type(_type)
{}

arcade::SolShot::~SolShot() {}

int arcade::SolShot::get_distRemaining() const {
    return _distRemaining;
}

arcade::SolShot::Type arcade::SolShot::get_typeShot() const {
    return _type;
}

void arcade::SolShot::set_distRemaining(int _distRemaining) {
    SolShot::_distRemaining = _distRemaining;
}

void arcade::SolShot::set_typeShot(arcade::SolShot::Type _type) {
    SolShot::_type = _type;
}