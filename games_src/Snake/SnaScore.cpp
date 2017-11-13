//
// Created by pierre on 14/03/17.
//

#include "SnaScore.hpp"

arcade::SnaScore::SnaScore() : _score(0) {}
arcade::SnaScore::~SnaScore() {

}

int arcade::SnaScore::get_score() const {
    return _score;
}

void arcade::SnaScore::operator+=(int a) {
    _score += a;
}

void arcade::SnaScore::set_score(int _score) {
    SnaScore::_score = _score;
}
