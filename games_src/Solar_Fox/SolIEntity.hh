//
// Created by pierre on 09/03/17.
//

#ifndef CPP_ARCADE_IENTITY_HH
#define CPP_ARCADE_IENTITY_HH

#include <chrono>
#include "SolPos.hpp"
#include "SolDirection.hpp"

namespace arcade {
    class SolIEntity {
    public:
        virtual const SolPos                   &get_positon() const = 0;
        virtual void                        set_positon(int x, int y) = 0;
        virtual double                      get_velocity() const = 0;
        virtual void                        set_velocity(double _velocity) = 0;
        virtual void                        set_distance(double _distance) = 0;
        virtual double                      get_distance() const = 0;
        virtual void                        set_newDirection(SolDirection::Axis direction) = 0;
        virtual void                        set_currentDirection(SolDirection::Axis direction) = 0;
        virtual const arcade::SolDirection     &get_direction() const = 0;
        virtual void                        moveUp() = 0;
        virtual void                        moveDown() = 0;
        virtual void                        moveRight() = 0;
        virtual void                        moveLeft() = 0;
    };
}

#endif //CPP_ARCADE_IENTITY_HH
