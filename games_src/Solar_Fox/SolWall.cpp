//
// Created by pierre on 11/04/17.
//

#include "SolWall.hpp"

arcade::SolWall::SolWall(int x, int y, arcade::SolDirection::Axis _currentDir, double _velocity) :
        SolEntity(x, y, _currentDir, _velocity)
{}

arcade::SolWall::~SolWall() {

}
