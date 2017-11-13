//
// Created by pierre on 08/04/17.
//

#include "SolEnemy.hpp"

arcade::SolEnemy::SolEnemy(int x, int y, SolDirection::Axis _currentDir, double _velocity) :
        SolEntity(x, y, _currentDir, _velocity),
        _timeSinceLastShot(std::chrono::high_resolution_clock::now()),
        _fireRate(10),
        _fireRange(100)
{}

arcade::SolEnemy::~SolEnemy() {}

void arcade::SolEnemy::setTimeSinceLastShot() {
    SolEnemy::_timeSinceLastShot = std::chrono::high_resolution_clock::now();
}

double arcade::SolEnemy::getTimeSinceLastShot() {
    double i = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _timeSinceLastShot).count();
    return i / 1000;
}

double arcade::SolEnemy::get_fireRate() const {
    return _fireRate;
}

void arcade::SolEnemy::set_fireRate(double _fireRate) {
    SolEnemy::_fireRate = _fireRate;
}

int arcade::SolEnemy::get_fireRange() const {
    return _fireRange;
}

void arcade::SolEnemy::set_fireRange(int _fireRange) {
    SolEnemy::_fireRange = _fireRange;
}
