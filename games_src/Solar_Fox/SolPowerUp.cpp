//
// Created by pierre on 11/04/17.
//

#include "SolPowerUp.hpp"

arcade::SolPowerUp::SolPowerUp(int x, int y, arcade::SolDirection::Axis _currentDir, double _velocity) :
        SolEntity(x, y, _currentDir, _velocity),
        _hp(2)
{}

arcade::SolPowerUp::~SolPowerUp() {}

int arcade::SolPowerUp::get_hp() const {
    return _hp;
}

void arcade::SolPowerUp::set_hp(int _hp) {
    SolPowerUp::_hp = _hp;
}
