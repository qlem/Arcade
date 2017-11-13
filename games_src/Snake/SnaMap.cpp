//
// Created by pierre on 08/03/17.
//

#include "SnaMap.hpp"

arcade::SnaMap::SnaMap() {}

arcade::SnaMap::~SnaMap() {
    //TODO delete tab int**
}

int arcade::SnaMap::getWidth() const {
    return _width;
}

int arcade::SnaMap::getHeight() const {
    return _height;
}

int arcade::SnaMap::getValue(const int x, const int y) const {
    return this->_map[y][x];
}

void arcade::SnaMap::setValue(const int x, const int y, Value n) {
    this->_map[y][x] = (char)n;
}

void arcade::SnaMap::initMap(int x, int y) {
    int     i = -1;
    int     j;

    set_width(x);
    set_height(y);
    _map = new char*[_height];
    for (auto n = 0; n < _height; ++n)
        this->_map[n] = new char[_width];
    while (++i < _height) {
        j= -1;
        while (++j < _width) {
            if (j == 0 || j == _width - 1 || i == 0 || i == _height - 1)
                setValue(j, i, Value::WALL);
            else
                setValue(j, i, Value::FREE);
        }
    }
}

void arcade::SnaMap::set_width(int _width) {
    SnaMap::_width = _width;
}

void arcade::SnaMap::set_height(int _height) {
    SnaMap::_height = _height;
}

char **arcade::SnaMap::get_map() const {
    return _map;
}
