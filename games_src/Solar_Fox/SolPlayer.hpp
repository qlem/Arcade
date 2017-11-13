//
// Created by pierre on 10/03/17.
//

#ifndef CPP_ARCADE_PLAYER_HPP
#define CPP_ARCADE_PLAYER_HPP

#include "SolEntity.hpp"

namespace arcade {
    class SolPlayer : public SolEntity
    {
    private:
        bool            _boosted;
        std::chrono::high_resolution_clock::time_point            _timeSinceLastShot;
        double          _fireRate;
        int             _fireRange;
        bool            _fire;

    public:
        SolPlayer(int x, int y, SolDirection::Axis _currentDir, double _velocity, bool boosted);
        SolPlayer();
        virtual ~SolPlayer();
        bool isBoosted() const;
        void setBoosted(bool boosted);
        void setTimeSinceLastShot();
        double getTimeSinceLastShot();
        double get_fireRate() const;
        void set_fireRate(double _fireRate);
        int get_fireRange() const;
        void set_fireRange(int _fireRange);
        void set_fire(bool _fire);
        bool is_fire() const;
    };
}

#endif //CPP_ARCADE_PLAYER_HPP