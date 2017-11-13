//
// Created by pierre on 10/03/17.
//

#include "SolPlayer.hpp"

arcade::SolPlayer::SolPlayer(int x, int y, SolDirection::Axis _currentDir, double _velocity, bool boosted) :
        SolEntity(x, y, _currentDir, _velocity),
        _boosted(false),
        _timeSinceLastShot(std::chrono::high_resolution_clock::now()),
        _fireRate(0.1),
        _fireRange(2),
        _fire(false)
{}

arcade::SolPlayer::SolPlayer() {}

arcade::SolPlayer::~SolPlayer() {}

bool arcade::SolPlayer::isBoosted() const {
    return _boosted;
}

void arcade::SolPlayer::setBoosted(bool boosted) {
    SolPlayer::_boosted = boosted;
}

void arcade::SolPlayer::setTimeSinceLastShot() {
    _timeSinceLastShot = std::chrono::high_resolution_clock::now();
}

double arcade::SolPlayer::getTimeSinceLastShot() {
    double i = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _timeSinceLastShot).count();
    return i / 1000;
}

double arcade::SolPlayer::get_fireRate() const {
    return _fireRate;
}

void arcade::SolPlayer::set_fireRate(double _fireRate) {
    SolPlayer::_fireRate = _fireRate;
}

int arcade::SolPlayer::get_fireRange() const {
    return _fireRange;
}

void arcade::SolPlayer::set_fireRange(int _fireRange) {
    SolPlayer::_fireRange = _fireRange;
}

bool arcade::SolPlayer::is_fire() const {
    return _fire;
}

void arcade::SolPlayer::set_fire(bool _fire) {
    SolPlayer::_fire = _fire;
}
