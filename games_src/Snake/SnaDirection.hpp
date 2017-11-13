//
// Created by pierre on 14/03/17.
//

#ifndef CPP_ARCADE_EVENT_HPP
#define CPP_ARCADE_EVENT_HPP

#include "SnaMap.hpp"

namespace arcade {
    class SnaDirection
    {
    public:
        enum class Axis {
            UP,
            DOWN,
            RIGHT,
            LEFT
        };

    private:
        Axis           _currentDir;
        Axis           _newDir;

    public:
        SnaDirection();
        virtual ~SnaDirection();
        Axis get_currentDir() const;
        void set_currentDir(Axis _direction);
        Axis get_newDir() const;
        void set_newDir(Axis _previousDirection);
    };
}

#endif //CPP_ARCADE_EVENT_HPP
