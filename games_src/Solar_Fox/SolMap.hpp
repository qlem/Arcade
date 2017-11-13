//
// Created by pierre on 08/03/17.
//

#ifndef CPP_ARCADE_MAP_HPP
#define CPP_ARCADE_MAP_HPP

#include "SolCreateLevels.hpp"

namespace arcade {
    enum class Value
    {
        PLAYER,
        POWERUP,
        WALL,
        ENEMY,
        SHOT,
        PLAYER_SHOT,
        FREE
    };

    class SolMap
    {
    private:
        int             _width;
        int             _height;
        char            **_map;
        SolLevelsCreator   _levelsC;

    public:
        SolMap(int mapWidth, int mapHeight);
        virtual ~SolMap();
        int             getWidth() const;
        int             getHeight() const;
        int             getValue(const int x, const int y) const;
        void            setValue(const int x, const int y, Value n);
        void            initMap(int lvl);
        void            initLevelDesign(int lvl);
    };
}

#endif //CPP_ARCADE_MAP_HPP