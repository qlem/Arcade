//
// Created by pierre on 14/03/17.
//

#ifndef CPP_ARCADE_POSITION_HPP
#define CPP_ARCADE_POSITION_HPP

namespace arcade {
    class SnaPos
    {
    private:
        int     _x;
        int     _y;

    public:
        SnaPos(int x, int y);
        SnaPos();
        virtual ~SnaPos();
        int get_x() const;
        int get_y() const;
        void set_x(int _x);
        void set_y(int _y);
    };
}

#endif //CPP_ARCADE_POSITION_HPP
