//
// Created by pierre on 11/04/17.
//

#ifndef TEST_ARCADE_POWERUP_HPP
#define TEST_ARCADE_POWERUP_HPP

#include "SolEntity.hpp"

namespace arcade {
    class SolPowerUp : public SolEntity
    {
    private:
        int         _hp;

    public:
        SolPowerUp(int x, int y, SolDirection::Axis _currentDir, double _velocity);
        virtual ~SolPowerUp();
        int get_hp() const;
        void set_hp(int _hp);
    };
}

#endif //TEST_ARCADE_POWERUP_HPP
