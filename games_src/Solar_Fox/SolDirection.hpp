//
// Created by pierre on 14/03/17.
//

#ifndef CPP_ARCADE_DIRECTION_HPP
#define CPP_ARCADE_DIRECTION_HPP

namespace arcade {
    class SolDirection
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
        SolDirection();
        SolDirection(Axis _direction);
        virtual ~SolDirection();
        Axis get_currentDir() const;
        Axis get_newDir() const;
        void set_currentDir(Axis _currentDir);
        void set_newDir(Axis _newDir);
    };
}

#endif //CPP_ARCADE_DIRECTION_HPP
