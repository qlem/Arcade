//
// Created by pierre on 08/04/17.
//

#ifndef TEST_ARCADE_ENEMY_HPP
#define TEST_ARCADE_ENEMY_HPP

#include "SolEntity.hpp"

namespace arcade {
    class SolEnemy : public SolEntity
    {
    private:
        std::chrono::high_resolution_clock::time_point            _timeSinceLastShot;
        double          _fireRate;
        int             _fireRange;

    public:
        SolEnemy(int x, int y, SolDirection::Axis _currentDir, double _velocity);
        virtual ~SolEnemy();
        void setTimeSinceLastShot();
        double getTimeSinceLastShot();
        double get_fireRate() const;
        void set_fireRate(double _fireRate);
        int get_fireRange() const;
        void set_fireRange(int _fireRange);
    };
}

#endif //TEST_ARCADE_ENEMY_HPP
