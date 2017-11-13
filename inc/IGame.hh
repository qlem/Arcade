//
// Created by dommer_c on 24/03/17.
//

#ifndef CPP_ARCADE_GAME_INTERFACE_H
#define CPP_ARCADE_GAME_INTERFACE_H

namespace arcade {

    class IGame {
    public:
        enum class State
        {
            RUN,
            OVER,
            WIN
        };

        enum class Event {
            UP,
            DOWN,
            RIGHT,
            LEFT,
            SHOOT,
            BOOST
        };

        enum class Color {
            WHITE,
            LIGHTGRAY,
            DARKGRAY,
            BLACK,
            BROWN,
            LIGHTRED,
            RED,
            YELLOW,
            LIGHTGREEN,
            GREEN,
            LIGHTBLUE,
            LIGHTCYAN,
            BLUE,
            LIGHTMAGENTA,
            MAGENTA,
            CYAN
        };

    public:
        virtual char                            **getMap() const = 0;
        virtual int                             getWidth() const = 0;
        virtual int                             getHeight() const = 0;
        virtual void                            saveEvent(Event event) = 0;
        virtual void                            update() = 0;
        virtual State                           getState() const = 0;
        virtual int                             getScore() const = 0;
        virtual const std::string               &getName() const = 0;
        virtual void                            startNewGame() = 0;
    };
}

#endif //CPP_ARCADE_GAME_INTERFACE_H