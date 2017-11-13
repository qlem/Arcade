//
// Created by dommer_c on 07/04/17.
//

#ifndef CPP_ARCADE_EVENT_H
#define CPP_ARCADE_EVENT_H


namespace arcade {

    class PacDirection {

    public:
        enum class      eDirection {
            RIGHT,
            LEFT,
            UP,
            DOWN,
            STOP
        };

    private:
        arcade::PacDirection::eDirection   _currentDirection;
        arcade::PacDirection::eDirection   _newDirection;

    public:
        PacDirection();
        PacDirection::eDirection    getCurrentDirection(void);
        PacDirection::eDirection    getNewDirection(void);
        void                     setCurrentDirection(PacDirection::eDirection direction);
        void                     setNewDirection(PacDirection::eDirection direction);
    };

}

#endif //CPP_ARCADE_EVENT_H
