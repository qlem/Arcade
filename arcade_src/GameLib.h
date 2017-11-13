//
// Created by raven57 on 07/04/17.
//

#ifndef CPP_ARCADE_GAMELIB_H
#define CPP_ARCADE_GAMELIB_H

#include <string>
#include "../inc/IGame.hh"

namespace arcade {

    class GameLib {
    private:
        std::string name = "";
        IGame *gameLib = NULL;

    public:
        GameLib();
        GameLib(const std::string &fileName, IGame *gameLib);
        ~GameLib();
        const std::string &getName() const;
        IGame *getGameLib() const;
    };

}
#endif //CPP_ARCADE_GAMELIB_H
