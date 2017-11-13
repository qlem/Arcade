//
// Created by pierre on 14/03/17.
//

#include "SolScore.hpp"

arcade::SolScore::SolScore() : _score(0) {}
arcade::SolScore::~SolScore() {

}

int arcade::SolScore::get_score() const {
    return _score;
}

void arcade::SolScore::operator+=(int a) {
    _score += a;
}

void arcade::SolScore::set_score(int _score) {
    SolScore::_score = _score;
}
