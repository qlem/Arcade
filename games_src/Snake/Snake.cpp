//
// Created by pierre on 16/03/17.
//

#include <iostream>
#include "Snake.hpp"

arcade::Snake::Snake() : _distance(0.0), _boosted(false) {}

arcade::Snake::~Snake() {

}

void arcade::Snake::set_head(const arcade::SnaPlayer &_head) {
    Snake::_head = _head;
}

const arcade::SnaPlayer &arcade::Snake::get_head() const {
    return _head;
}

const std::deque<std::unique_ptr<arcade::SnaTailSection>> &arcade::Snake::get_tail() const {
    return _tail;
}

void arcade::Snake::moveUp() {
    _tail.emplace_front(new SnaTailSection(_head.get_positon().get_x(), _head.get_positon().get_y()));
    _head.set_positon(_head.get_positon().get_x(), _head.get_positon().get_y() - 1);
    _tail.pop_back();
}

void arcade::Snake::moveDown() {
    _tail.emplace_front(new SnaTailSection(_head.get_positon().get_x(), _head.get_positon().get_y()));
    _head.set_positon(_head.get_positon().get_x(), _head.get_positon().get_y() + 1);
    _tail.pop_back();
}

void arcade::Snake::moveRight() {
    _tail.emplace_front(new SnaTailSection(_head.get_positon().get_x(), _head.get_positon().get_y()));
    _head.set_positon(_head.get_positon().get_x() + 1, _head.get_positon().get_y());
    _tail.pop_back();
}

void arcade::Snake::moveLeft() {
    _tail.emplace_front(new SnaTailSection(_head.get_positon().get_x(), _head.get_positon().get_y()));
    _head.set_positon(_head.get_positon().get_x() - 1, _head.get_positon().get_y());
    _tail.pop_back();
}

double arcade::Snake::get_distance() const {
    return _distance;
}

void arcade::Snake::set_distance(double _timer) {
    Snake::_distance = _timer;
}

void arcade::Snake::addNewTailSec(const SnaPos &position) {
    _tail.emplace_back(new SnaTailSection(position.get_x(), position.get_y()));
}

void arcade::Snake::spawn(int x, int y) {
    x /= 2;
    y /= 2;
    x = x - 2;
    std::deque<std::unique_ptr<SnaTailSection>>::iterator it;

    _head.set_positon(x, y);
    for (it = _tail.begin(); it != _tail.end(); ++it)
        (*it)->set_positon(++x, y);
}

double arcade::Snake::get_velocity() const {
    return _velocity;
}

void arcade::Snake::set_velocity(double _velocity) {
    Snake::_velocity = _velocity;
}

bool arcade::Snake::is_boosted() const {
    return _boosted;
}

void arcade::Snake::set_boosted(bool _boosted) {
    Snake::_boosted = _boosted;
}

void arcade::Snake::resetTail() {
        _tail.clear();
        _tail.emplace_back( new SnaTailSection());
        _tail.emplace_back( new SnaTailSection());
        _tail.emplace_back( new SnaTailSection());
}