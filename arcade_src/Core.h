//
// Created by dommer_c on 24/03/17.
//

#ifndef CPP_ARCADE_CORE_H
#define CPP_ARCADE_CORE_H

#include <chrono>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <iostream>
#include "../inc/IGraphic.hh"
#include "../inc/IGame.hh"
#include "LibLoader.h"
#include "GraphicLib.h"
#include "GameLib.h"
#include "Scoring.h"

#define WIDTH_MENU 30
#define HEIGHT_MENU 20

namespace arcade {

    class Core {

    public:
        enum class   WindowEvent {
            QUIT,
            MENU,
            PLAY,
            WIN,
            OVER
        };

    private:
        std::vector<GraphicLib>                     _graphicLibs;
        std::vector<GameLib>                        _gameLibs;
        std::vector<GraphicLib>::iterator           _itGraphicLibs;
        std::vector<GameLib>::iterator              _itGameLibs;
        std::vector<arcade::IGraphic::Key>          _events;
        std::vector<arcade::IGraphic::Key>          _eventsDeletable;
        IGame                                       *_currentGame;
        IGraphic                                    *_currentLib;
        Core::WindowEvent                           _windowEvent;

        bool                                        _alreadyLaunched;
        arcade::Scoring                             _scoring;
        std::vector<std::pair<std::string, int>>    _scoresTab;
        bool                                        _nameValidate;

    public:
        Core();
        bool    init_uis(const char *defaultUi);
        bool    load_library(const std::string &libraryName, bool isDefault);
        void    run();

        arcade::IGraphic::Color translateColor(arcade::IGame::Color color);
        void    render();
        void    drawMenuBoard();
        void    drawEndGameBoard(int isWin);
        void    manageEvents(void);
        void    eraseEvents();
        void    changeGraphic(int a);
        void    changeGame(int a);
        void    restartGame();
        void    enterEvent();
        void    escapeEvent();
    };

}
#endif //CPP_ARCADE_CORE_H

