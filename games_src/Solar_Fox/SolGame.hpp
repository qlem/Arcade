//
// Created by pierre on 14/03/17.
//

#ifndef CPP_ARCADE_GAME_HPP
#define CPP_ARCADE_GAME_HPP

#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include <cstdlib>
#include "SolMap.hpp"
#include "SolScore.hpp"
#include "SolDirection.hpp"
#include "../../inc/IGame.hh"
#include "SolEntity.hpp"
#include "SolPlayer.hpp"
#include "SolEnemy.hpp"
#include "SolPowerUp.hpp"
#include "SolWall.hpp"
#include "SolShot.hpp"
#include "SolPos.hpp"

#define mapWidth 20
#define mapHeight 20
#define dt (1.0 / 60.0)
#define RAND(a, b) rand()%(b-a)+a

namespace arcade {
    class SolGame : public IGame
    {
    protected:
        SolMap                                             _map;
        char                                            **_coreMap;
        SolScore                                           _score;
        IGame::State                                    _state;
        SolPlayer                                          _player;
        std::vector<std::unique_ptr<SolEnemy>>             _enemies;
        std::vector<std::unique_ptr<SolShot>>              _shots;
        std::vector<std::unique_ptr<SolPowerUp>>           _powerUps;
        std::vector<std::unique_ptr<SolWall>>              _walls;
        std::vector<Event>                              _events;
        int                                             _level;
        std::string                                     _name;
        bool                                            _nextLvl;
        std::chrono::time_point<std::chrono::high_resolution_clock> _tStart;

    public:
        SolGame();
        virtual                                 ~SolGame();
        void                                    initCoreMap();
        const                                   SolMap &get_map() const;
        void                                    convertMap();
        virtual char                            **getMap() const;
        virtual int                             getWidth() const;
        virtual int                             getHeight() const;
        virtual void                            update();
        virtual void                            processEvent();
        virtual IGame::State                    getState() const;
        virtual int                             getScore() const;
        void                                    initEntities();
        void                                    removeEntities();
        void                                    clearEntitiesInMap();
        void                                    setEntitiesInMap();
        virtual void                            saveEvent(Event event);
        bool                                    checkIn(std::vector<Event> &_events, Event event);
        void                                    printEvents();
        void                                    botControl();
        void                                    playerControl();
        void                                    shotControl();
        void                                    shotCollision();
        bool                                    inCollision(int x, int y);
        void                                    removeEntitiesInCollision(int x, int y);
        void                                    initLevel(int lvl);
        virtual const std::string               &getName() const;
        virtual void                            startNewGame();
    };
}

#endif //CPP_ARCADE_GAME_HPP