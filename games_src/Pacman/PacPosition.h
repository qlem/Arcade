//
// Created by dommer_c on 07/04/17.
//

#ifndef CPP_ARCADE_POSITION_H
#define CPP_ARCADE_POSITION_H


namespace arcade {

    class PacPosition {
    private:
        int     _x;
        int     _y;

    public:
        int     getX();
        int     getY();
        void    setX(int x);
        void    setY(int y);
    };

}

#endif //CPP_ARCADE_POSITION_H
