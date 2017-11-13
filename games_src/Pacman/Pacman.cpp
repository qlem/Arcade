//
// Created by dommer_c on 29/03/17.
//

#include "Pacman.h"

extern "C" arcade::Pacman* create_object()
{
    return new arcade::Pacman;
}

extern "C" void destroy_object(arcade::Pacman* object)
{
    delete object;
}

arcade::Pacman::Pacman() {
    this->_width = 19;
    this->_height = 17;
    this->_map = new char *[this->_height];
    for (auto n = 0; n < this->_height; ++n)
        this->_map[n] = new char[this->_width];
    this->setMap();
    this->setEntites();
    this->setEntitieOnMap();
    this->_state = arcade::IGame::State::RUN;
    this->_name = "Pacman";
    this->_score = 0;
}

char **arcade::Pacman::getMap(void) const {
    return this->_map;
}

int arcade::Pacman::getWidth(void) const {
    return this->_width;
}

int arcade::Pacman::getHeight(void) const {
    return this->_height;
}

void arcade::Pacman::saveEvent(arcade::IGame::Event event) {
    if (this->_events.size() == 2)
        this->_events.erase(this->_events.end() - 1);
    this->_events.push_back(event);
}

void arcade::Pacman::update(void) {
    double dt = 1.0 / 60.0;
    for (std::vector<arcade::PacEntities>::iterator i = this->_entities.begin(); i != this->_entities.end(); i++) {

        (*i).setDistance((*i).getDistance() + (dt * (*i).getVelocity()));

        if ((*i).getIsAlive() == arcade::PacEntities::isAlive::ALIVE) {

            switch ((*i).getCondition()) {
                case arcade::PacEntities::Condition::PLAYER :
                    if (this->_events.size() > 0)
                        processEventPlayer(*i);
                    break;
                case arcade::PacEntities::Condition::AGGRESSIVE :
                    processEventAI(*i);
                    break;
                case arcade::PacEntities::Condition::HARMLESS :
                    if ((*i).getHarmlessDuration() >= 10.0)
                        this->endBigPacgumEvent(*i);
                    processEventAI(*i);
                    break;
                default:
                    break;
            }

            if ((*i).getDistance() >= 1 && ((*i).getCondition() == arcade::PacEntities::Condition::PLAYER ||
                                            (*i).getCondition() == arcade::PacEntities::Condition::HARMLESS ||
                                            (*i).getCondition() == arcade::PacEntities::Condition::AGGRESSIVE)) {
                this->checkNewDirection(*i);
                this->checkCurrentDirection(*i);
            }
        }
    }
    this->eraeseEntities();
    this->setEntitieOnMap();
    if (this->checkWin())
        this->_state = arcade::IGame::State::WIN;
}

arcade::IGame::State arcade::Pacman::getState() const {
    return this->_state;
}

int arcade::Pacman::getScore() const {
    return this->_score;
}


const std::string &arcade::Pacman::getName() const {
    return this->_name;
}

void arcade::Pacman::startNewGame() {
    this->_events.clear();
    this->_entities.clear();
    this->_state = arcade::IGame::State::RUN;
    this->setMap();
    this->setEntites();
    this->setEntitieOnMap();
    this->_score = 0;
}

void arcade::Pacman::setEntites() {
    this->_entities.push_back(arcade::PacEntities(9, 10, arcade::PacEntities::Condition::PLAYER, 3.0, arcade::PacEntities::isAlive::ALIVE));
    this->_entities.push_back(arcade::PacEntities(8, 8, arcade::PacEntities::Condition::AGGRESSIVE, 3.0, arcade::PacEntities::isAlive::ALIVE));
    this->_entities.push_back(arcade::PacEntities(9, 8, arcade::PacEntities::Condition::AGGRESSIVE, 3.0, arcade::PacEntities::isAlive::ALIVE));
    this->_entities.push_back(arcade::PacEntities(10, 8, arcade::PacEntities::Condition::AGGRESSIVE, 3.0, arcade::PacEntities::isAlive::ALIVE));
    this->_entities.push_back(arcade::PacEntities(9, 6, arcade::PacEntities::Condition::AGGRESSIVE, 3.0, arcade::PacEntities::isAlive::ALIVE));
}

void arcade::Pacman::setMap(void) {
    for (int y = 0; y < this->_height; y++) {
        for (int x = 0; x < this->_width; x++) {
            switch (this->_modele[y][x]) {
                case 1:
                    this->_map[y][x] = (char)arcade::IGame::Color::BLUE;
                    break;
                case 2:
                    this->_entities.push_back(arcade::PacEntities(x, y, arcade::PacEntities::Condition::PACGUM, 0.0, arcade::PacEntities::isAlive::ALIVE));
                    break;
                case 3:
                    this->_entities.push_back(arcade::PacEntities(x, y, arcade::PacEntities::Condition::BIGPACGUM, 0.0, arcade::PacEntities::isAlive::ALIVE));
                    break;
                case 4:
                    this->_map[y][x] = (char)arcade::IGame::Color::BLACK;
                    break;
                default:
                    break;
            }
        }
    }
}

void arcade::Pacman::setEntitieOnMap() {
    int x;
    int y;

    for (std::vector<arcade::PacEntities>::iterator it = this->_entities.begin(); it != this->_entities.end(); it++) {
        x = (*it).getPosition().getX();
        y = (*it).getPosition().getY();
        switch ((*it).getCondition()) {
            case arcade::PacEntities::Condition::PACGUM :
                this->_map[y][x] = (char) arcade::IGame::Color::LIGHTBLUE;
                break;
            case arcade::PacEntities::Condition::BIGPACGUM :
                this->_map[y][x] = (char) arcade::IGame::Color::LIGHTGREEN;
                break;
            case arcade::PacEntities::Condition::AGGRESSIVE :
                this->_map[y][x] = (char) arcade::IGame::Color::RED;
                break;
            case arcade::PacEntities::Condition::HARMLESS :
                this->_map[y][x] = (char) arcade::IGame::Color::MAGENTA;
                break;
            case arcade::PacEntities::Condition::PLAYER :
                this->_map[y][x] = (char) arcade::IGame::Color::YELLOW;
                break;
        }
    }
}

void arcade::Pacman::processEventPlayer(arcade::PacEntities &entitie) {
    switch (this->_events.back()) {
        case arcade::IGame::Event::UP :
            entitie.setNewDirection(arcade::PacDirection::eDirection::UP);
            break;
        case arcade::IGame::Event::DOWN :
            entitie.setNewDirection(arcade::PacDirection::eDirection::DOWN);
            break;
        case arcade::IGame::Event::LEFT :
            entitie.setNewDirection(arcade::PacDirection::eDirection::LEFT);
            break;
        case arcade::IGame::Event::RIGHT :
            entitie.setNewDirection(arcade::PacDirection::eDirection::RIGHT);
            break;
        default:
            break;
    }
}

void arcade::Pacman::processEventAI(arcade::PacEntities &entitie) {
    int x = entitie.getPosition().getX();
    int y = entitie.getPosition().getY();

    switch (entitie.getDirection().getCurrentDirection()) {


        case arcade::PacDirection::eDirection::UP :
            if (this->_map[y][x + 1] != (char)arcade::IGame::Color::BLUE ||
                this->_map[y][x - 1] != (char)arcade::IGame::Color::BLUE)
                switch (getRandomNumber(2)) {
                    case 1 :
                        entitie.setNewDirection(arcade::PacDirection::eDirection::LEFT);
                        break;
                    case 2 :
                        entitie.setNewDirection(arcade::PacDirection::eDirection::RIGHT);
                        break;
                    default:
                        break;
                }
            break;


        case arcade::PacDirection::eDirection::DOWN :
            if (this->_map[y][x + 1] != (char)arcade::IGame::Color::BLUE ||
                this->_map[y][x - 1] != (char)arcade::IGame::Color::BLUE)
                switch (getRandomNumber(2)) {
                    case 1 :
                        entitie.setNewDirection(arcade::PacDirection::eDirection::LEFT);
                        break;
                    case 2 :
                        entitie.setNewDirection(arcade::PacDirection::eDirection::RIGHT);
                        break;
                    default:
                        break;
                }
            break;


        case arcade::PacDirection::eDirection::LEFT :
            if (this->_map[y - 1][x] != (char)arcade::IGame::Color::BLUE ||
                this->_map[y + 1][x] != (char)arcade::IGame::Color::BLUE)
                switch (getRandomNumber(2)) {
                    case 1 :
                        entitie.setNewDirection(arcade::PacDirection::eDirection::UP);
                        break;
                    case 2 :
                        entitie.setNewDirection(arcade::PacDirection::eDirection::DOWN);
                        break;
                    default:
                        break;
                }
            break;


        case arcade::PacDirection::eDirection::RIGHT :
            if (this->_map[y - 1][x] != (char)arcade::IGame::Color::BLUE ||
                this->_map[y + 1][x] != (char)arcade::IGame::Color::BLUE)
                switch (getRandomNumber(2)) {
                    case 1 :
                        entitie.setNewDirection(arcade::PacDirection::eDirection::UP);
                        break;
                    case 2 :
                        entitie.setNewDirection(arcade::PacDirection::eDirection::DOWN);
                        break;
                    default:
                        break;
                }
            break;


        default:
            switch (getRandomNumber(4)) {
                case 1 :
                    entitie.setNewDirection(arcade::PacDirection::eDirection::UP);
                    break;
                case 2 :
                    entitie.setNewDirection(arcade::PacDirection::eDirection::DOWN);
                    break;
                case 3:
                    entitie.setNewDirection(arcade::PacDirection::eDirection::LEFT);
                    break;
                case 4:
                    entitie.setNewDirection(arcade::PacDirection::eDirection::RIGHT);
                    break;
                default:
                    break;
            }
            break;
    }
}

int arcade::Pacman::getRandomNumber(int max) {
    int                         random;
    std::random_device          r;
    std::default_random_engine  e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, max);
    random = uniform_dist(e1);
    return random;
}

void arcade::Pacman::checkNewDirection(arcade::PacEntities &entitie) {
    int     x;
    int     y;

    x = entitie.getPosition().getX();
    y = entitie.getPosition().getY();
    switch (entitie.getDirection().getNewDirection()) {
        case arcade::PacDirection::eDirection::UP :
            if (this->_map[y - 1][x] != (char) arcade::IGame::Color::BLUE) {
                entitie.setCurrentDirection(arcade::PacDirection::eDirection::UP);
                if (entitie.getCondition() == arcade::PacEntities::Condition::PLAYER && this->_events.size())
                    this->_events.erase(this->_events.begin());
            }
            break;
        case arcade::PacDirection::eDirection::DOWN :
            if (this->_map[y + 1][x] != (char) arcade::IGame::Color::BLUE) {
                entitie.setCurrentDirection(arcade::PacDirection::eDirection::DOWN);
                if (entitie.getCondition() == arcade::PacEntities::Condition::PLAYER && this->_events.size())
                    this->_events.erase(this->_events.begin());
            }
            break;
        case arcade::PacDirection::eDirection::LEFT :
            if (x == 0 || this->_map[y][x - 1] != (char) arcade::IGame::Color::BLUE) {
                entitie.setCurrentDirection(arcade::PacDirection::eDirection::LEFT);
                if (entitie.getCondition() == arcade::PacEntities::Condition::PLAYER && this->_events.size())
                    this->_events.erase(this->_events.begin());
            }
            break;
        case arcade::PacDirection::eDirection::RIGHT :
            if (x == 18 || this->_map[y][x + 1] != (char) arcade::IGame::Color::BLUE) {
                entitie.setCurrentDirection(arcade::PacDirection::eDirection::RIGHT);
                if (entitie.getCondition() == arcade::PacEntities::Condition::PLAYER && this->_events.size())
                    this->_events.erase(this->_events.begin());
            }
            break;
        default:
            break;
    }
}

void arcade::Pacman::checkCurrentDirection(arcade::PacEntities &entitie) {
    int     x;
    int     y;

    x = entitie.getPosition().getX();
    y = entitie.getPosition().getY();
    switch (entitie.getDirection().getCurrentDirection()) {
        case arcade::PacDirection::eDirection::UP:
            if (this->_map[y - 1][x] != (char) arcade::IGame::Color::BLUE) {
                this->checkCollision(x, y - 1, entitie);
                this->_map[y][x] = (char)arcade::IGame::Color::BLACK;
                entitie.moveUp();
                entitie.setDistance(0.0);
            }
            else
                entitie.setCurrentDirection(arcade::PacDirection::eDirection::STOP);
            break;

        case arcade::PacDirection::eDirection::DOWN:
            if (this->_map[y + 1][x] != (char) arcade::IGame::Color::BLUE) {
                this->checkCollision(x, y + 1, entitie);
                this->_map[y][x] = (char)arcade::IGame::Color::BLACK;
                entitie.moveDown();
                entitie.setDistance(0.0);
            }
            else
                entitie.setCurrentDirection(arcade::PacDirection::eDirection::STOP);
            break;

        case arcade::PacDirection::eDirection::LEFT:
            if (x == 0 || this->_map[y][x - 1] != (char) arcade::IGame::Color::BLUE) {
                if (x == 0)
                    this->checkCollision(18, y, entitie);
                else
                    this->checkCollision(x - 1, y, entitie);
                this->_map[y][x] = (char)arcade::IGame::Color::BLACK;
                entitie.moveLeft();
                entitie.setDistance(0.0);
            }
            else
                entitie.setCurrentDirection(arcade::PacDirection::eDirection::STOP);
            break;

        case arcade::PacDirection::eDirection::RIGHT:
            if (x == 18 || this->_map[y][x + 1] != (char) arcade::IGame::Color::BLUE) {
                if (x == 18)
                    this->checkCollision(0, y, entitie);
                else
                    this->checkCollision(x + 1, y, entitie);
                this->_map[y][x] = (char)arcade::IGame::Color::BLACK;
                entitie.moveRight();
                entitie.setDistance(0.0);
            }
            else
                entitie.setCurrentDirection(arcade::PacDirection::eDirection::STOP);
            break;

        default:
            break;
    }
}

void arcade::Pacman::checkCollision(int x, int y, arcade::PacEntities &entitie) {
    switch (entitie.getCondition()) {

        case arcade::PacEntities::Condition::HARMLESS :
            if (this->isOnEntitie(x, y, arcade::PacEntities::Condition::PLAYER)) {
                this->_entities.push_back(arcade::PacEntities(9, 8, arcade::PacEntities::Condition::AGGRESSIVE, 3.0, arcade::PacEntities::isAlive::ALIVE));
                entitie.setIsAlive(arcade::PacEntities::isAlive::DEAD);
                this->_score += 200;
            }
            break;

        case arcade::PacEntities::Condition::AGGRESSIVE :
            if (this->isOnEntitie(x, y, arcade::PacEntities::Condition::PLAYER))
                this->_state = arcade::IGame::State::OVER;
            break;

        case arcade::PacEntities::Condition::PLAYER :
            if (this->isOnEntitie(x, y, arcade::PacEntities::Condition::AGGRESSIVE))
                this->_state = arcade::IGame::State::OVER;
            if (this->isOnEntitie(x, y, arcade::PacEntities::Condition::HARMLESS)) {
                this->_entities.push_back(arcade::PacEntities(9, 8, arcade::PacEntities::Condition::AGGRESSIVE, 3.0,
                                                           arcade::PacEntities::isAlive::ALIVE));
                this->_score += 200;
            }
            if (this->isOnEntitie(x, y, arcade::PacEntities::Condition::BIGPACGUM)) {
                this->startBigPacgumEvent();
                this->_score += 50;
            }
            if (this->isOnEntitie(x, y, arcade::PacEntities::Condition::PACGUM))
                this->_score += 10;
            break;

        default:
            break;
    }
}

bool arcade::Pacman::isOnEntitie(int x, int y, arcade::PacEntities::Condition condition) {
    std::vector<arcade::PacEntities>::iterator it;
    bool    check = false;

    for (it = this->_entities.begin(); it != this->_entities.end(); it++) {
        if ((*it).getCondition() == condition &&
            x == (*it).getPosition().getX() && y == (*it).getPosition().getY()) {
            check = true;
            if ((*it).getCondition() != arcade::PacEntities::Condition::PLAYER && (*it).getCondition() != arcade::PacEntities::Condition::AGGRESSIVE)
                (*it).setIsAlive(arcade::PacEntities::isAlive::DEAD);
        }
    }
    return check;
}

// ITERATION PROBLEMATIQUE OU PEUT ETRE PAS
void arcade::Pacman::startBigPacgumEvent(void) {
    std::vector<arcade::PacEntities>::iterator it;

    for (it = this->_entities.begin(); it != this->_entities.end(); it++) {
        if ((*it).getCondition() == arcade::PacEntities::Condition::AGGRESSIVE ||
                (*it).getCondition() == arcade::PacEntities::Condition::HARMLESS) {
            (*it).setCondition(arcade::PacEntities::Condition::HARMLESS);
            (*it).setVelocity(2.0);
            (*it).resetHarmlessDuration();
        }
    }
}

void arcade::Pacman::endBigPacgumEvent(arcade::PacEntities &entitie) {
    entitie.setVelocity(3.0);
    entitie.setCondition(arcade::PacEntities::Condition::AGGRESSIVE);
}

void arcade::Pacman::eraeseEntities(void) {
    std::vector<arcade::PacEntities>::iterator        it;

    for (it = this->_entities.begin(); it != this->_entities.end(); it++) {
        switch ((*it).getIsAlive()) {
            case arcade::PacEntities::isAlive::DEAD :
                this->_entities.erase(it);
                break;
            default:
                break;
        }
    }
}

bool arcade::Pacman::checkWin() {
    std::vector<arcade::PacEntities>::iterator     it;
    bool    isWin;

    isWin = true;
    for (it = this->_entities.begin(); it != this->_entities.end(); it++) {
        if ((*it).getCondition() == arcade::PacEntities::Condition::PACGUM ||
                (*it).getCondition() == arcade::PacEntities::Condition::BIGPACGUM)
            isWin = false;
    }
    return isWin;
}

arcade::PacDirection::eDirection arcade::Pacman::trackPacman(arcade::PacEntities &entitie) {
    int     x;
    int     y;
    arcade::PacDirection::eDirection    direction;
    int     xEntitie = entitie.getPosition().getX();
    int     yEntitie = entitie.getPosition().getY();

    direction = arcade::PacDirection::eDirection::STOP;
    for (y = yEntitie - 3; y != yEntitie + 3; y++) {
        for (x = xEntitie - 3; x != xEntitie + 3; x++) {
            if (isOnEntitie(x, y, arcade::PacEntities::Condition::PLAYER)) {

                if (y == yEntitie && (x >= xEntitie - 3 && x <= xEntitie - 1))
                    direction = arcade::PacDirection::eDirection::LEFT;

                else if (y == yEntitie && (x <= xEntitie + 3 && x >= xEntitie + 1))
                    direction = arcade::PacDirection::eDirection::RIGHT;

                else if (x == xEntitie && (y >= yEntitie - 3 && y <= yEntitie - 1))
                    direction = arcade::PacDirection::eDirection::UP;

                else if (x == xEntitie && (y <= yEntitie + 3 && y >= yEntitie + 1))
                    direction = arcade::PacDirection::eDirection::DOWN;

                else if ((x >= xEntitie - 3 && x <= xEntitie - 1) && (y >= yEntitie - 3 && y <= yEntitie - 1)) {
                    switch (this->getRandomNumber(2)) {
                        case 1 :
                            direction = arcade::PacDirection::eDirection::UP;
                            break;
                        case 2 :
                            direction = arcade::PacDirection::eDirection::LEFT;
                            break;
                        default:
                            break;
                    }
                }

                else if ((x <= xEntitie + 3 && x >= xEntitie + 1) && (y >= yEntitie - 3 && y <= yEntitie - 1)) {
                    switch (this->getRandomNumber(2)) {
                        case 1 :
                            direction = arcade::PacDirection::eDirection::UP;
                            break;
                        case 2 :
                            direction = arcade::PacDirection::eDirection::RIGHT;
                            break;
                        default:
                            break;
                    }
                }

                else if ((x >= xEntitie - 3 && x <= xEntitie - 1) && (y <= yEntitie + 3 && y >= yEntitie + 1)) {
                    switch (this->getRandomNumber(2)) {
                        case 1 :
                            direction = arcade::PacDirection::eDirection::DOWN;
                            break;
                        case 2 :
                            direction = arcade::PacDirection::eDirection::LEFT;
                            break;
                        default:
                            break;
                    }
                }

                else if ((x <= xEntitie + 3 && x >= xEntitie + 1) && (y <= yEntitie + 3 && y >= yEntitie + 1)) {
                    switch (this->getRandomNumber(2)) {
                        case 1 :
                            direction = arcade::PacDirection::eDirection::DOWN;
                            break;
                        case 2 :
                            direction = arcade::PacDirection::eDirection::RIGHT;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    return direction;
}
