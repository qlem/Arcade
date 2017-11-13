//
// Created by pierre on 07/04/17.
//

#ifndef TEST_ARCADE_ENTITY_HPP
#define TEST_ARCADE_ENTITY_HPP

#include "SolIEntity.hh"

namespace arcade {
    class SolEntity : public SolIEntity {
    protected:
        SolPos                                 _position;
        SolDirection                           _direction;
        double                              _velocity;
        double                              _distance;

    public:
        SolEntity();
        SolEntity(int x, int y, SolDirection::Axis _currentDir, double _velocity);
        virtual ~SolEntity();
        virtual const SolPos                   &get_positon() const;
        virtual void                        set_positon(int x, int y);
        virtual double                      get_velocity() const;
        virtual void                        set_velocity(double velocity);
        virtual void                        set_distance(double distance);
        virtual double                      get_distance() const;
        virtual void                        set_newDirection(SolDirection::Axis direction);
        virtual void                        set_currentDirection(SolDirection::Axis direction);
        virtual const arcade::SolDirection     &get_direction() const;
        virtual void                        moveUp();
        virtual void                        moveDown();
        virtual void                        moveRight();
        virtual void                        moveLeft();
    };
}

#endif //TEST_ARCADE_ENTITY_HPP
