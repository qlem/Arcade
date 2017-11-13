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
#include "SnaMap.hpp"
#include "SnaScore.hpp"
#include "Snake.hpp"
#include "SnaDirection.hpp"
#include "SnaFood.hpp"
#include "../../inc/IGame.hh"

#define mapWidth 25
#define mapHeight 25
#define dt (1.0 / 60.0)
#define RAND(a, b) rand()%(b-a)+a

namespace arcade {
    class SnaGame : public IGame
    {
    private:
        SnaMap                                             _map;
        char                                            **_coreMap;
        Snake                                           _snake;
        SnaScore                                           _score;
        State                                           _state;
        std::vector<Event>                              _events;
        SnaDirection                                       _direction;
        std::vector<std::unique_ptr<SnaFood>>              _food;
        std::string                                     _name;
        std::chrono::time_point<std::chrono::high_resolution_clock> _tStart;

    public:
        SnaGame();
        virtual                                 ~SnaGame();
        void                                    spawnNewFood();
        void                                    initCoreMap();
        void                                    removeFood(int x, int y);
        const                                   SnaMap &get_map() const;
        void                                    convertMap();
        virtual char                            **getMap() const;
        virtual int                             getWidth() const;
        virtual int                             getHeight() const;
        virtual void                            update();
        virtual void                            saveEvent(Event event);
        virtual State                           getState() const;
        virtual int                             getScore() const;
        void                                    processEvent();
        bool                                    checkIn(std::vector<Event> &_events, Event event);
        virtual const std::string               &getName() const;
        virtual void                            startNewGame();
        virtual void                            setEntitiesInMap();
    };
}

#endif //CPP_ARCADE_GAME_HPP