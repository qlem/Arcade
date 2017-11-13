//
// Created by pierre on 16/03/17.
//

#ifndef CPP_ARCADE_SNAKE_HPP
#define CPP_ARCADE_SNAKE_HPP

#include <deque>
#include <bits/unique_ptr.h>
#include "SnaPlayer.hpp"
#include "SnaTailSection.hpp"

namespace arcade {
    class Snake
    {
    private:
        SnaPlayer                      _head;
        std::deque<std::unique_ptr<SnaTailSection>>     _tail;
        double                      _distance;
        double                      _velocity;
        bool                        _boosted;

    public:
        virtual ~Snake();
        Snake();
        void set_head(const SnaPlayer &_head);
        const SnaPlayer &get_head() const;
        const std::deque<std::unique_ptr<SnaTailSection>> &get_tail() const;
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void addNewTailSec(const SnaPos &);
        void set_distance(double _distance);
        double get_distance() const;
        void spawn(int x, int y);
        double get_velocity() const;
        void set_velocity(double _velocity);
        bool is_boosted() const;
        void set_boosted(bool _boosted);
        void resetTail();
    };
}

#endif //CPP_ARCADE_SNAKE_HPP
