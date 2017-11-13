//
// Created by pierre on 11/04/17.
//

#ifndef TEST_ARCADE_WALL_HPP
#define TEST_ARCADE_WALL_HPP

#include "SolEntity.hpp"

namespace arcade {
    class SolWall : public SolEntity
    {
    public:
        SolWall(int x, int y, SolDirection::Axis _currentDir, double _velocity);
        virtual ~SolWall();
    };
}

#endif //TEST_ARCADE_WALL_HPP
