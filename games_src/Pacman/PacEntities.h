//
// Created by dommer_c on 07/04/17.
//

#ifndef CPP_ARCADE_ENTITIES_H
#define CPP_ARCADE_ENTITIES_H

#include <chrono>
#include "PacPosition.h"
#include "PacDirection.h"

namespace arcade {

    class PacEntities {

    public:
        enum class          Condition {
            AGGRESSIVE,
            HARMLESS,
            PLAYER,
            PACGUM,
            BIGPACGUM
        };

        enum class          isAlive {
            ALIVE,
            DEAD
        };

    private:
        arcade::PacPosition        _position;
        arcade::PacEntities::Condition _condition;
        arcade::PacDirection           _direction;
        double                      _velocity;
        double                      _distance;
        isAlive                     _isAlive;
        std::chrono::high_resolution_clock::time_point      _harmlessDuration;

    public:
        PacEntities();
        PacEntities(int x, int y, Condition state, double velocity, arcade::PacEntities::isAlive isAlive);

        arcade::PacPosition    getPosition(void);

        void    moveUp();
        void    moveDown();
        void    moveLeft();
        void    moveRight();

        arcade::PacEntities::Condition  getCondition(void);
        void                            setCondition(Condition condition);

        void                    setNewDirection(arcade::PacDirection::eDirection direction);
        void                    setCurrentDirection(arcade::PacDirection::eDirection direction);
        arcade::PacDirection    getDirection(void);

        double  getVelocity() const;
        void    setVelocity(double _velocity);
        double  getDistance() const;
        void    setDistance(double _distance);

        double  getHarmlessDuration();
        void    resetHarmlessDuration();

        void                             setIsAlive(arcade::PacEntities::isAlive state);
        arcade::PacEntities::isAlive     getIsAlive(void);
    };

}

#endif //CPP_ARCADE_ENTITIES_H
