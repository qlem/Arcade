//
// Created by pierre on 08/04/17.
//

#ifndef TEST_ARCADE_SHOT_HPP
#define TEST_ARCADE_SHOT_HPP

#include "SolEntity.hpp"

namespace arcade {
    class SolShot : public SolEntity
    {
    public:
        enum class Type {
            PLAYER,
            ENEMY
        };

    private:
        int             _distRemaining;
        Type            _type;

    public:
        SolShot(int x, int y, SolDirection::Axis _currentDir, double _velocity, int _distRemaining, Type _type);
        virtual ~SolShot();
        int get_distRemaining() const;
        Type get_typeShot() const;
        void set_distRemaining(int _distRemaining);
        void set_typeShot(Type _type);
    };
}

#endif //TEST_ARCADE_SHOT_HPP
