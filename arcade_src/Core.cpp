//
// Created by dommer_c on 24/03/17.
//

#include "Core.h"

arcade::Core::Core()
{
    this->_windowEvent = arcade::Core::WindowEvent::MENU;
    this->_alreadyLaunched = false;
    this->_nameValidate = false;
}

static bool getdir(const std::string& dir, std::vector<std::string>& files)
{
    DIR *dp;
    struct dirent *dirp;
    std::string s;

    if ((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error while opening " << dir << std::endl;
        return false;
    }

    while ((dirp = readdir(dp)) != NULL) {
        s = std::string(dir + "/");
        s += std::string(dirp->d_name);
        files.push_back(s);
    }
    closedir(dp);
    return true;
}

bool arcade::Core::load_library(const std::string &libraryName, bool isDefault)
{
    bool        boResult = false;
    std::size_t found;
    void        *handle;
    std::string name;
    LibLoader   loader;

    found = libraryName.find_last_of("/");
    name = libraryName.substr(found+1);

    for (std::vector<GraphicLib>::iterator i = _graphicLibs.begin(); i != _graphicLibs.end(); ++i) {
        if ((*i).getName() == name)
            return false;
    }

    handle = loader.openLib(libraryName);
    if (handle) {

        if (libraryName.substr(0, found) == "./lib" or isDefault)
        {
            IGraphic    *(*create)();

            create = (IGraphic *(*)()) loader.loadSymbol(handle, "create_object");
            if (create) {
                GraphicLib graphicLib(name, create());
                //destroy = (void (*)(IGraphic *)) loader.loadSymbol(handle, "destroy_object")
                _graphicLibs.push_back(graphicLib);
                boResult = true;
            }
        }
        else if (libraryName.substr(0, found) == "./games")
        {
            IGame       *(*create)();

            create = (IGame *(*)()) loader.loadSymbol(handle, "create_object");
            if (create) {
                GameLib gameLib(name, create());
                //destroy = (void (*)(IGame *)) loader.loadSymbol(handle, "destroy_object")
                _gameLibs.push_back(gameLib);
                boResult = true;
            }
        }
        if (!boResult)
            loader.closeLib(handle);
    }
    return boResult;
}

bool arcade::Core::init_uis(const char *defaultUi)
{
    std::vector<std::string> files = std::vector<std::string>();

    load_library(defaultUi, true);
    getdir("./lib", files);
    getdir("./games", files);
    for (std::vector<std::string>::iterator i = files.begin(); i != files.end(); ++i) {
        load_library(*i, false);
    }

    return (_graphicLibs.size() != 0);
}

void arcade::Core::run()
{
    if (_graphicLibs.size() && _gameLibs.size()) {

        this->_itGraphicLibs = this->_graphicLibs.begin();
        this->_itGameLibs = this->_gameLibs.begin();

        this->_currentGame = (*this->_itGameLibs).getGameLib();
        this->_currentLib = (*this->_itGraphicLibs).getGraphicLib();

        this->_currentLib->createDisplay(WIDTH_MENU, HEIGHT_MENU);

        double dt = 1.0 / 60.0;
        double accumulator = 0.0;
        auto t1 = std::chrono::high_resolution_clock::now();
        double frameTime;

        while (this->_windowEvent != arcade::Core::WindowEvent::QUIT) {

            auto t2 = std::chrono::high_resolution_clock::now();
            frameTime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
            frameTime /= 1000000;
            t1 = t2;

            if (this->_currentGame->getState() == arcade::IGame::State::OVER) {
                if (this->_windowEvent != arcade::Core::WindowEvent::OVER)
                    this->_currentLib->resizeDisplay(WIDTH_MENU, HEIGHT_MENU);
                this->_windowEvent = arcade::Core::WindowEvent::OVER;
            }
            else if (this->_currentGame->getState() == arcade::IGame::State::WIN) {
                if (this->_windowEvent != arcade::Core::WindowEvent::WIN)
                    this->_currentLib->resizeDisplay(WIDTH_MENU, HEIGHT_MENU);
                this->_windowEvent = arcade::Core::WindowEvent::WIN;
            }

            this->manageEvents();
            this->eraseEvents();

            this->_currentLib->clearDisplay();

            switch (this->_windowEvent) {

                case arcade::Core::WindowEvent::MENU :
                    this->drawMenuBoard();
                    break;
                case arcade::Core::WindowEvent::PLAY :
                    accumulator += frameTime;
                    while (accumulator >= dt) {
                        this->_currentGame->update();
                        accumulator -= dt;
                    }
                    this->render();
                    break;
                case arcade::Core::WindowEvent::WIN :
                    this->drawEndGameBoard(1);
                    break;
                case arcade::Core::WindowEvent::OVER :
                    this->drawEndGameBoard(0);
                    break;
                default:
                    break;
            }
            this->_currentLib->refreshDisplay();
        }
        this->_currentLib->destroyDisplay();
    }
}

arcade::IGraphic::Color arcade::Core::translateColor(arcade::IGame::Color color) {
    arcade::IGraphic::Color     colorGFX;

    switch (color) {
        case arcade::IGame::Color::WHITE :
            colorGFX = arcade::IGraphic::Color::WHITE;
            break;
        case arcade::IGame::Color::LIGHTGRAY :
            colorGFX = arcade::IGraphic::Color::LIGHTGRAY;
            break;
        case arcade::IGame::Color::DARKGRAY :
            colorGFX = arcade::IGraphic::Color::DARKGRAY;
            break;
        case arcade::IGame::Color::BLACK :
            colorGFX = arcade::IGraphic::Color::BLACK;
            break;
        case arcade::IGame::Color::BROWN :
            colorGFX = arcade::IGraphic::Color::BROWN;
            break;
        case arcade::IGame::Color::LIGHTRED :
            colorGFX = arcade::IGraphic::Color::LIGHTRED;
            break;
        case arcade::IGame::Color::RED :
            colorGFX = arcade::IGraphic::Color::RED;
            break;
        case arcade::IGame::Color::YELLOW :
            colorGFX = arcade::IGraphic::Color::YELLOW;
            break;
        case arcade::IGame::Color::LIGHTGREEN :
            colorGFX = arcade::IGraphic::Color::LIGHTGREEN;
            break;
        case arcade::IGame::Color::GREEN :
            colorGFX = arcade::IGraphic::Color::GREEN;
            break;
        case arcade::IGame::Color::LIGHTBLUE :
            colorGFX = arcade::IGraphic::Color::LIGHTBLUE;
            break;
        case arcade::IGame::Color::LIGHTCYAN :
            colorGFX = arcade::IGraphic::Color::LIGHTCYAN;
            break;
        case arcade::IGame::Color::BLUE :
            colorGFX = arcade::IGraphic::Color::BLUE;
            break;
        case arcade::IGame::Color::LIGHTMAGENTA :
            colorGFX = arcade::IGraphic::Color::LIGHTMAGENTA;
            break;
        case arcade::IGame::Color::MAGENTA :
            colorGFX = arcade::IGraphic::Color::MAGENTA;
            break;
        case arcade::IGame::Color::CYAN :
            colorGFX = arcade::IGraphic::Color::CYAN;
            break;
    }
    return colorGFX;
}

void arcade::Core::render() {
    int     x;
    int     y;
    char    **map;

    map = this->_currentGame->getMap();
    for (y = 0; y < this->_currentGame->getHeight(); y++) {
        for (x = 0; x <this->_currentGame->getWidth(); x++)
            this->_currentLib->draw(x, y, translateColor((arcade::IGame::Color) map[y][x]));
    }
    this->_currentLib->writeText(1, this->_currentGame->getHeight(), "Score : ", arcade::IGraphic::Color::WHITE, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(5, this->_currentGame->getHeight(), std::to_string(this->_currentGame->getScore()), arcade::IGraphic::Color::WHITE, arcade::IGraphic::Style::REGULAR);
}

void arcade::Core::drawEndGameBoard(int isWin) {
    std::vector<std::pair<std::string, int>>::iterator      it;
    int     y;

    if (this->_nameValidate) {
        this->_currentLib->writeText(20, 7, this->_currentLib->getTextEntered(), arcade::IGraphic::Color::WHITE,
                                     arcade::IGraphic::Style::REGULAR);
        this->_currentLib->writeText(10, 17, "Press R to restart", arcade::IGraphic::Color::WHITE,
                                     arcade::IGraphic::Style::REGULAR);
    }
    else {
        this->_currentLib->setTextEntryMod(true);
        this->_currentLib->writeText(20, 7, this->_currentLib->getTextEntered(), arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
        this->_currentLib->writeText(6, 17, "Enter to validate - 3 characters", arcade::IGraphic::Color::WHITE, arcade::IGraphic::Style::REGULAR);
    }
    switch (isWin) {
        case 0 :
            this->_currentLib->writeText(12, 2, "YOU LOSE !", arcade::IGraphic::Color::RED, arcade::IGraphic::Style::REGULAR);
            break;
        case 1 :
            this->_currentLib->writeText(12, 2, "YOU WIN !", arcade::IGraphic::Color::GREEN, arcade::IGraphic::Style::REGULAR);
            break;
        default:
            break;
    }
    this->_currentLib->writeText(10, 5, "Your Score : ", arcade::IGraphic::Color::WHITE, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(18, 5, std::to_string(this->_currentGame->getScore()), arcade::IGraphic::Color::WHITE, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(9, 7, "Enter your name : ", arcade::IGraphic::Color::WHITE, arcade::IGraphic::Style::REGULAR);
    y = 8;
    for (it = this->_scoresTab.begin(); it != this->_scoresTab.end() && it != this->_scoresTab.begin() + 3; it++) {
        this->_currentLib->writeText(11, y = y + 2, (*it).first, arcade::IGraphic::Color::WHITE, arcade::IGraphic::Style::REGULAR);
        this->_currentLib->writeText(16, y, std::to_string((*it).second), arcade::IGraphic::Color::WHITE, arcade::IGraphic::Style::REGULAR);
    }
}

void arcade::Core::drawMenuBoard() {
    std::vector<GraphicLib>::iterator   i;
    std::vector<GameLib>::iterator      j;
    int                                 y;

    this->_currentLib->writeText(1, 2, "MENU", arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(1, 5, "Graphics", arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(15, 5, "Games", arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(1, 12, "A - Z   Switch graphic", arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(1, 13, "Q - S   Switch game", arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(1, 14, "R       Restart game", arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(1, 15, "ESCAPE  Pause - Display this menu", arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    this->_currentLib->writeText(1, 17, "ENTER   Play", arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    y = 6;
    for (i = this->_graphicLibs.begin(); i != this->_graphicLibs.end(); i++) {
        if ((*i).getGraphicLib() == this->_currentLib)
            this->_currentLib->writeText(3, ++y, (*i).getGraphicLib()->getName(), arcade::IGraphic::Color::RED, arcade::IGraphic::Style::REGULAR);
        else
            this->_currentLib->writeText(3, ++y, (*i).getGraphicLib()->getName(), arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    }
    y = 6;
    for (j = this->_gameLibs.begin(); j != this->_gameLibs.end(); j++) {
        if ((*j).getGameLib() == this->_currentGame)
            this->_currentLib->writeText(17, ++y, (*j).getGameLib()->getName(), arcade::IGraphic::Color::RED, arcade::IGraphic::Style::REGULAR);
        else
            this->_currentLib->writeText(17, ++y, (*j).getGameLib()->getName(), arcade::IGraphic::Color::LIGHTGRAY, arcade::IGraphic::Style::REGULAR);
    }
}

void arcade::Core::eraseEvents() {
    std::vector<arcade::IGraphic::Key>::iterator    i;
    std::vector<arcade::IGraphic::Key>::iterator    j;

    for (i = this->_eventsDeletable.begin(); i != this->_eventsDeletable.end(); i++) {
        for (j = this->_events.begin(); j != this->_events.end();) {
            if (*i == *j)
                j = this->_events.erase(j);
            else
                j++;
        }
    }
    this->_eventsDeletable.clear();
}

void arcade::Core::manageEvents(void) {
    std::vector<arcade::IGraphic::Key>::iterator it;

    this->_currentLib->catchInput(this->_events);
    if (this->_events.size() > 0) {
        for (it = this->_events.begin(); it != this->_events.end(); it++) {
            switch (*it) {
                case arcade::IGraphic::Key::KEY_LEFT :
                    this->_currentGame->saveEvent(arcade::IGame::Event::LEFT);
                    break;

                case arcade::IGraphic::Key::KEY_RIGHT :
                    this->_currentGame->saveEvent(arcade::IGame::Event::RIGHT);
                    break;

                case arcade::IGraphic::Key::KEY_UP :
                    this->_currentGame->saveEvent(arcade::IGame::Event::UP);
                    break;

                case arcade::IGraphic::Key::KEY_DOWN :
                    this->_currentGame->saveEvent(arcade::IGame::Event::DOWN);
                    break;

                case arcade::IGraphic::Key::KEY_A :
                    this->changeGraphic(0);
                    this->_eventsDeletable.push_back(arcade::IGraphic::Key::KEY_A);
                    break;

                case arcade::IGraphic::Key::KEY_C :
                    this->_currentGame->saveEvent(arcade::IGame::Event::BOOST);
                    break;

                case arcade::IGraphic::Key::KEY_Q :
                    this->changeGame(0);
                    this->_eventsDeletable.push_back(arcade::IGraphic::Key::KEY_Q);
                    break;

                case arcade::IGraphic::Key::KEY_R :
                    this->restartGame();
                    this->_eventsDeletable.push_back(arcade::IGraphic::Key::KEY_R);
                    break;

                case arcade::IGraphic::Key::KEY_S :
                    this->changeGame(1);
                    this->_eventsDeletable.push_back(arcade::IGraphic::Key::KEY_S);
                    break;

                case arcade::IGraphic::Key::KEY_Z :
                    this->changeGraphic(1);
                    this->_eventsDeletable.push_back(arcade::IGraphic::Key::KEY_Z);
                    break;

                case arcade::IGraphic::Key::KEY_QUIT :
                    this->_windowEvent = arcade::Core::WindowEvent::QUIT;
                    this->_eventsDeletable.push_back(arcade::IGraphic::Key::KEY_QUIT);
                    break;

                case arcade::IGraphic::Key::KEY_ESCAPE :
                    this->escapeEvent();
                    this->_eventsDeletable.push_back(arcade::IGraphic::Key::KEY_ESCAPE);
                    break;

                case arcade::IGraphic::Key::KEY_ENTER :
                    this->enterEvent();
                    this->_eventsDeletable.push_back(arcade::IGraphic::Key::KEY_ENTER);
                    break;

                case arcade::IGraphic::Key::KEY_SPACE :
                    this->_currentGame->saveEvent(arcade::IGame::Event::SHOOT);
                    break;

                default:
                    break;
            }
        }
    }
}

void arcade::Core::changeGraphic(int a) {
    switch (a) {
        case 0 :
            this->_currentLib->destroyDisplay();
            if (this->_itGraphicLibs == this->_graphicLibs.begin()) {
                this->_itGraphicLibs = this->_graphicLibs.end() - 1;
            } else
                this->_itGraphicLibs--;
            break;

        case 1 :
            this->_currentLib->destroyDisplay();
            if (this->_itGraphicLibs == this->_graphicLibs.end() - 1)
                this->_itGraphicLibs = this->_graphicLibs.begin();
            else
                this->_itGraphicLibs++;
            break;

        default:
            break;
    }
    this->_currentLib = (*this->_itGraphicLibs).getGraphicLib();
    switch (this->_windowEvent) {
        case arcade::Core::WindowEvent::PLAY :
            this->_currentLib->createDisplay(this->_currentGame->getWidth(), this->_currentGame->getHeight() + 1);
            break;
        default:
            this->_currentLib->createDisplay(WIDTH_MENU, HEIGHT_MENU);
            break;
    }
}

void arcade::Core::changeGame(int a) {
    if (this->_windowEvent == arcade::Core::WindowEvent::PLAY || this->_windowEvent == arcade::Core::WindowEvent::MENU) {
        switch (a) {
            case 0 :
                if (this->_itGameLibs == this->_gameLibs.begin())
                    this->_itGameLibs = this->_gameLibs.end() - 1;
                else
                    this->_itGameLibs--;
                this->_currentGame = (*this->_itGameLibs).getGameLib();
                break;

            case 1 :
                if (this->_itGameLibs == this->_gameLibs.end() - 1)
                    this->_itGameLibs = this->_gameLibs.begin();
                else
                    this->_itGameLibs++;
                this->_currentGame = (*this->_itGameLibs).getGameLib();
                break;

            default:
                break;
        }
        switch (this->_windowEvent) {
            case arcade::Core::WindowEvent::PLAY :
                this->_currentLib->resizeDisplay(this->_currentGame->getWidth(), this->_currentGame->getHeight() + 1);
                break;
            default:
                break;
        }
        this->_scoresTab  = this->_scoring.getScores(this->_currentGame->getName());
    }
}

void arcade::Core::restartGame() {
    switch (this->_windowEvent) {
        case arcade::Core::WindowEvent::PLAY :
            this->_currentGame->startNewGame();
            break;
        case arcade::Core::WindowEvent::WIN :
            this->_currentLib->resizeDisplay(this->_currentGame->getWidth(), this->_currentGame->getHeight() + 1);
            this->_currentGame->startNewGame();
            this->_windowEvent = arcade::Core::WindowEvent::PLAY;
            this->_nameValidate = false;
            break;
        case arcade::Core::WindowEvent::OVER :
            this->_currentLib->resizeDisplay(this->_currentGame->getWidth(), this->_currentGame->getHeight() + 1);
            this->_currentGame->startNewGame();
            this->_windowEvent = arcade::Core::WindowEvent::PLAY;
            this->_nameValidate = false;
            break;
        default:
            break;
    }
}

void arcade::Core::enterEvent() {
    switch (this->_windowEvent) {
        case arcade::Core::WindowEvent::MENU :
            this->_scoresTab = this->_scoring.getScores(this->_currentGame->getName());
            this->_alreadyLaunched = true;
            this->_windowEvent = arcade::Core::WindowEvent::PLAY;
            this->_currentLib->resizeDisplay(this->_currentGame->getWidth(), this->_currentGame->getHeight() + 1);
            break;
        case arcade::Core::WindowEvent::WIN:
            if (!this->_nameValidate && this->_currentLib->getTextEntered().size() == 3) {
                this->_nameValidate = true;
                this->_currentLib->setTextEntryMod(false);
                this->_scoring.saveScore(this->_currentGame->getName(), this->_currentLib->getTextEntered(),
                                         this->_currentGame->getScore());
                this->_scoresTab = this->_scoring.getScores(this->_currentGame->getName());
            }
            break;
        case arcade::Core::WindowEvent::OVER:
            if (!this->_nameValidate && this->_currentLib->getTextEntered().size() == 3) {
                this->_nameValidate = true;
                this->_currentLib->setTextEntryMod(false);
                this->_scoring.saveScore(this->_currentGame->getName(), this->_currentLib->getTextEntered(),
                                         this->_currentGame->getScore());
                this->_scoresTab = this->_scoring.getScores(this->_currentGame->getName());
            }
            break;
        default:
            break;
    }
}

void arcade::Core::escapeEvent() {
    switch (this->_windowEvent) {
        case arcade::Core::WindowEvent::PLAY :
            this->_windowEvent = arcade::Core::WindowEvent::MENU;
            this->_currentLib->resizeDisplay(WIDTH_MENU, HEIGHT_MENU);
            break;
        case arcade::Core::WindowEvent::MENU :
            if (this->_alreadyLaunched) {
                this->_windowEvent = arcade::Core::WindowEvent::PLAY;
                this->_currentLib->resizeDisplay(this->_currentGame->getWidth(), this->_currentGame->getHeight() + 1);
            }
            break;
        case arcade::Core::WindowEvent::OVER :
            if (!this->_nameValidate) {
                this->_currentLib->setTextEntryMod(false);
                this->_scoring.saveScore(this->_currentGame->getName(), "UNK",
                                         this->_currentGame->getScore());
            }
            this->_currentGame->startNewGame();
            this->_windowEvent = arcade::Core::WindowEvent::MENU;
            this->_currentLib->resizeDisplay(WIDTH_MENU, HEIGHT_MENU);
            break;
        case arcade::Core::WindowEvent::WIN :
            if (!this->_nameValidate) {
                this->_currentLib->setTextEntryMod(false);
                this->_scoring.saveScore(this->_currentGame->getName(), "UNK",
                                         this->_currentGame->getScore());
            }
            this->_currentGame->startNewGame();
            this->_windowEvent = arcade::Core::WindowEvent::MENU;
            this->_currentLib->resizeDisplay(WIDTH_MENU, HEIGHT_MENU);
            break;
        default:
            break;
    }
}
