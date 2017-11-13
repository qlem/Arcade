//
// Created by pierre on 08/03/17.
//

#include "SolMap.hpp"

arcade::SolMap::SolMap(int mapWidth, int mapHeight) :
        _width(mapWidth),
        _height(mapHeight),
        _levelsC(mapWidth, mapHeight)
{}

arcade::SolMap::~SolMap() {
    for( int i=0; i<_height; ++i ) {
        delete[] _map[i];
    }
    delete[] _map;
}

int arcade::SolMap::getWidth() const {
    return _width;
}

int arcade::SolMap::getHeight() const {
    return _height;
}

int arcade::SolMap::getValue(const int x, const int y) const {
    return _map[y][x];
}

void arcade::SolMap::setValue(const int x, const int y, Value n) {
    _map[y][x] = (char)n;
}

void    arcade::SolMap::initLevelDesign(int n)
{
    int x;
    int y = -1;

    while (++y < _height) {
        x= -1;
        while (++x < _width) {
            if (_levelsC.getValue(x, y, n) == 2)
                setValue(x, y, Value::WALL);
            else if (_levelsC.getValue(x, y, n) == 1)
                setValue(x, y, Value::POWERUP);
            else if (_levelsC.getValue(x, y, n) == 3)
                setValue(x, y, Value::PLAYER);
            else
                setValue(x, y, Value::FREE);
        }
    }
}

void arcade::SolMap::initMap(int lvl) {
    _map = new char*[_height];
    for (auto n = 0; n < _height; ++n)
        this->_map[n] = new char[_width];
    initLevelDesign(lvl);
}
