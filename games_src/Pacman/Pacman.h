//
// Created by dommer_c on 29/03/17.
//

#ifndef CPP_ARCADE_PACMAN_H
#define CPP_ARCADE_PACMAN_H

#include <string>
#include <random>
#include <vector>
#include "../../inc/IGame.hh"
#include "PacEntities.h"

namespace arcade {

    class Pacman : public arcade::IGame {

    private:
        arcade::IGame::State                _state;
        int                                 _width;
        int                                 _height;
        std::vector<arcade::PacEntities>       _entities;
        char                                **_map;
        std::vector<arcade::IGame::Event>   _events;
        std::string                         _name;
        int                                 _score;
        char                                _modele[17][19] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
                {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
                {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
                {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
                {1, 2, 2, 2, 2, 1, 4, 4, 4, 4, 4, 4, 4, 1, 2, 2, 2, 2, 1},
                {1, 1, 1, 1, 2, 1, 4, 1, 1, 4, 1, 1, 4, 1, 2, 1, 1, 1, 1},
                {2, 2, 2, 2, 2, 2, 4, 1, 4, 4, 4, 1, 4, 2, 2, 2, 2, 2, 2},
                {1, 1, 1, 1, 2, 1, 4, 1, 1, 1, 1, 1, 4, 1, 2, 1, 1, 1, 1},
                {1, 2, 2, 2, 2, 1, 4, 4, 4, 4, 4, 4, 4, 1, 2, 2, 2, 2, 1},
                {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
                {1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
                {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
                {1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
                {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };

    public:
        Pacman();
        char    **getMap(void) const;
        int     getWidth(void) const;
        int     getHeight(void) const;
        void    saveEvent(IGame::Event event);
        void    update(void);
        arcade::IGame::State   getState() const;
        int     getScore() const;
        const std::string   &getName() const;
        void    startNewGame();


    private:
        void    setEntites();
        void    setMap(void);
        void    setEntitieOnMap();


        int     getRandomNumber(int  max);
        void    processEventAI(arcade::PacEntities &entitie);
        void    processEventPlayer(arcade::PacEntities &entitie);

        void    checkNewDirection(arcade::PacEntities &entitie);
        void    checkCurrentDirection(arcade::PacEntities &entitie);

        void    checkCollision(int x, int y, arcade::PacEntities &entitie);

        void    startBigPacgumEvent(void);
        void    endBigPacgumEvent(arcade::PacEntities &entitie);

        void    eraeseEntities(void);
        bool    isOnEntitie(int x, int y, arcade::PacEntities::Condition condition);

        bool checkWin();
        arcade::PacDirection::eDirection    trackPacman(arcade::PacEntities &entitie);
    };

}

#endif //CPP_ARCADE_PACMAN_H
