//
// Created by pierre on 14/03/17.
//

#include "SolGame.hpp"

extern "C" arcade::SolGame* create_object()
{
    return new arcade::SolGame();
}

extern "C" void destroy_object(arcade::SolGame* object)
{
    delete object;
}

arcade::SolGame::SolGame() :
        _map(mapWidth, mapHeight),
        _state(State::RUN),
        _level(1),
        _name("Solar Fox"),
        _nextLvl(false)
{
    startNewGame();
    srand((unsigned int) time(nullptr));
}

arcade::SolGame::~SolGame() {
    for( int i=0; i<mapHeight; ++i ) {
        delete[] _coreMap[i];
    }
    delete[] _coreMap;
}

void arcade::SolGame::startNewGame() {
    _level = 1;
    initLevel(_level);
    _state = State::RUN;
    _score.set_score(0);
    _tStart = std::chrono::high_resolution_clock::now();
    _nextLvl = false;
}

void arcade::SolGame::initLevel(int lvl) {
    removeEntities();
    _map.initMap(lvl);
    initEntities();
    initCoreMap();
    _player.set_distance(0.0);
    _player.set_fire(false);
    _player.setBoosted(false);
    _player.setTimeSinceLastShot();
    convertMap();
}

void arcade::SolGame::update()
{
    if (_nextLvl)
    {
        if (_level == 3) {
            _state = State::WIN;
            return;
        }
        initLevel(_level + 1);
        _level += 1;
        _nextLvl = false;
    }
    processEvent();
    shotControl();
    playerControl();
    botControl();
    clearEntitiesInMap();
    setEntitiesInMap();
    if (_powerUps.empty())
        _nextLvl = true;
    convertMap();
}

void    arcade::SolGame::initEntities()
{
    int x;
    int y = -1;
    while (++y < _map.getHeight()) {
        x= -1;
        while (++x < _map.getWidth()) {
            if (_map.getValue(x, y) == (int) Value::WALL)
                _walls.emplace_back(new SolWall(x, y, SolDirection::Axis::RIGHT, 0));
            else if (_map.getValue(x, y) == (int) Value::POWERUP)
                _powerUps.emplace_back(new SolPowerUp(x, y, SolDirection::Axis::RIGHT, 0));
            else if (_map.getValue(x, y) == (int) Value::PLAYER)
                _player = SolPlayer(x, y, SolDirection::Axis::UP, 3.0, false);
        }
    }
    _enemies.emplace_back(new SolEnemy(3, 0, SolDirection::Axis::RIGHT, 5.0));
    _enemies.emplace_back(new SolEnemy(mapWidth - 4, mapHeight - 1, SolDirection::Axis::LEFT, 5.0));
    _enemies.emplace_back(new SolEnemy(0, mapHeight - 4, SolDirection::Axis::UP, 5.0));
    _enemies.emplace_back(new SolEnemy(mapWidth - 1, 3, SolDirection::Axis::DOWN, 5.0));
}

bool arcade::SolGame::checkIn(std::vector<arcade::IGame::Event> &_events, arcade::IGame::Event event) {
    std::vector<Event>::iterator it;

    for(it = _events.begin(); it!=_events.end(); ++it)
        if (*it == event)
            return true;
    return false;
}

void arcade::SolGame::saveEvent(arcade::IGame::Event event) {
    if (!checkIn(_events, event))
        _events.push_back(event);
}

void arcade::SolGame::processEvent() {
    std::vector<Event>::iterator it;

    //printEvents();
    for (it = _events.begin(); it != _events.end();) {
        switch (*it) {
            case Event::UP:
                if (_player.get_direction().get_currentDir() != SolDirection::Axis::DOWN)
                    _player.set_newDirection(SolDirection::Axis::UP);
                _events.erase(it);
                break;
            case Event::DOWN:
                if (_player.get_direction().get_currentDir() != SolDirection::Axis::UP)
                    _player.set_newDirection(SolDirection::Axis::DOWN);
                _events.erase(it);
                break;
            case Event::RIGHT:
                if (_player.get_direction().get_currentDir() != SolDirection::Axis::LEFT)
                    _player.set_newDirection(SolDirection::Axis::RIGHT);
                _events.erase(it);
                break;
            case Event::LEFT:
                if (_player.get_direction().get_currentDir() != SolDirection::Axis::RIGHT)
                    _player.set_newDirection(SolDirection::Axis::LEFT);
                _events.erase(it);
                break;
            case Event::SHOOT:
                if (_player.getTimeSinceLastShot() > _player.get_fireRate()) {
                    _player.setTimeSinceLastShot();
                    _player.set_fire(true);
                }
                _events.erase(it);
                break;
            case Event::BOOST:
                _player.setBoosted(true);
                _events.erase(it);
                break;
        }
    }
}

const arcade::SolMap &arcade::SolGame::get_map() const {
    return _map;
}

char        **arcade::SolGame::getMap() const {
    return _coreMap;
}

int arcade::SolGame::getWidth() const {
    return get_map().getWidth();
}

int arcade::SolGame::getHeight() const {
    return get_map().getHeight();
}

void        arcade::SolGame::convertMap() {
    int     y = -1;
    int     x;

    while (++y < _map.getHeight()) {
        x = -1;
        while (++x < _map.getWidth()) {
            switch (_map.getValue(x, y)) {
                case (int) Value::WALL:
                    _coreMap[y][x] = (char) Color::LIGHTGRAY;
                    break;
                case (int) Value::PLAYER:
                    _coreMap[y][x] = (char) Color::LIGHTGREEN;
                    break;
                case (int) Value::ENEMY:
                    _coreMap[y][x] = (char) Color::BROWN;
                    break;
                case (int) Value::POWERUP:
                    _coreMap[y][x] = (char) Color::MAGENTA;
                    break;
                case (int) Value::SHOT:
                    _coreMap[y][x] = (char) Color::RED;
                    break;
                case (int) Value::PLAYER_SHOT:
                    _coreMap[y][x] = (char) Color::BLUE;
                    break;
                case (int) Value::FREE:
                    _coreMap[y][x] = (char) Color::BLACK;
                    break;
                default:
                    _coreMap[y][x] = (char) Color::BLACK;
                    break;
            }
        }
    }
}

void        arcade::SolGame::initCoreMap() {
    _coreMap = new char*[mapHeight];
    for (auto n = 0; n < mapHeight; ++n)
        _coreMap[n] = new char[mapWidth];
}

arcade::IGame::State arcade::SolGame::getState() const {
    return _state;
}

int arcade::SolGame::getScore() const {
    return _score.get_score();
}

void    arcade::SolGame::setEntitiesInMap()
{
    std::vector<std::unique_ptr<SolEnemy>>::iterator it;
    std::vector<std::unique_ptr<SolShot>>::iterator it2;
    std::vector<std::unique_ptr<SolWall>>::iterator it3;
    std::vector<std::unique_ptr<SolPowerUp>>::iterator it4;

    _map.setValue(_player.get_positon().get_x(), _player.get_positon().get_y(), Value::PLAYER);
    for (it = _enemies.begin(); it != _enemies.end(); ++it)
        _map.setValue((*it)->get_positon().get_x(), (*it)->get_positon().get_y(), Value::ENEMY);
    for (it3 = _walls.begin(); it3 != _walls.end(); ++it3)
        _map.setValue((*it3)->get_positon().get_x(), (*it3)->get_positon().get_y(), Value::WALL);
    for (it4 = _powerUps.begin(); it4 != _powerUps.end(); ++it4)
        _map.setValue((*it4)->get_positon().get_x(), (*it4)->get_positon().get_y(), Value::POWERUP);
    for (it2 = _shots.begin(); it2 != _shots.end(); ++it2) {
        if ((*it2)->get_typeShot() == SolShot::Type::ENEMY)
            _map.setValue((*it2)->get_positon().get_x(), (*it2)->get_positon().get_y(), Value::SHOT);
        else
            _map.setValue((*it2)->get_positon().get_x(), (*it2)->get_positon().get_y(), Value::PLAYER_SHOT);
    }
}

void arcade::SolGame::clearEntitiesInMap() {
    int     y = -1;
    int     x;

    while (++y < _map.getHeight()) {
        x = -1;
        while (++x < _map.getWidth()) {
            if (_map.getValue(x, y) == (int) Value::PLAYER
                || _map.getValue(x, y) == (int) Value::ENEMY
                || _map.getValue(x, y) == (int) Value::POWERUP
                || _map.getValue(x, y) == (int) Value::PLAYER_SHOT
                || _map.getValue(x, y) == (int) Value::SHOT)
                _map.setValue(x, y, Value::FREE);
        }
    }
}

void arcade::SolGame::printEvents() {
    std::vector<Event>::iterator it;
    std::cout << "/////////////////" << std::endl;
    for (it = _events.begin(); it != _events.end(); ++it)
    {
        switch (*it)
        {
            case Event::UP:
                std::cout << "UP" << std::endl;
                break;
            case Event::LEFT:
                std::cout << "LEFT" << std::endl;
                break;
            case Event::RIGHT:
                std::cout << "RIGHT" << std::endl;
                break;
            case Event::DOWN:
                std::cout << "DOWN" << std::endl;
                break;
            case Event::SHOOT:
                std::cout << "SPACE" << std::endl;
                break;
            case Event::BOOST:
                std::cout << "F" << std::endl;
                break;
        }
    }
    std::cout << "/////////////////" << std::endl;
}

void arcade::SolGame::botControl() {
    std::vector<std::unique_ptr<SolEnemy>>::iterator it;

    for (it = _enemies.begin(); it != _enemies.end(); ++it) {
        (*it)->set_distance((*it)->get_distance() + (dt * (*it)->get_velocity()));
        if ((*it)->get_distance() >= 1) {
            switch ((*it)->get_direction().get_currentDir()) {
                case SolDirection::Axis::LEFT:
                    if ((*it)->get_positon().get_x() > 3)
                        (*it)->moveLeft();
                    else if ((*it)->get_positon().get_x() == 3)
                        (*it)->set_currentDirection(SolDirection::Axis::RIGHT);
                    break;
                case SolDirection::Axis::RIGHT:
                    if ((*it)->get_positon().get_x() < mapWidth - 4)
                        (*it)->moveRight();
                    else if ((*it)->get_positon().get_x() == mapWidth - 4)
                        (*it)->set_currentDirection(SolDirection::Axis::LEFT);
                    break;
                case SolDirection::Axis::UP:
                    if ((*it)->get_positon().get_y() > 3)
                        (*it)->moveUp();
                    else if ((*it)->get_positon().get_y() == 3)
                        (*it)->set_currentDirection(SolDirection::Axis::DOWN);
                    break;
                case SolDirection::Axis::DOWN:
                    if ((*it)->get_positon().get_y() < mapHeight - 4)
                        (*it)->moveDown();
                    else if ((*it)->get_positon().get_y() == mapHeight - 4)
                        (*it)->set_currentDirection(SolDirection::Axis::UP);
                    break;
            }
            (*it)->set_distance(0);
        }
    }

    int     r;
    for (it = _enemies.begin(); it != _enemies.end(); ++it) {
        r = RAND(0, 200);
        if (r == 3 && (*it)->getTimeSinceLastShot() > (*it)->get_fireRate())
        {
            if (((*it)->get_direction().get_currentDir() == SolDirection::Axis::RIGHT
                 || (*it)->get_direction().get_currentDir() == SolDirection::Axis::LEFT)
                && (*it)->get_positon().get_x() > 2
                && (*it)->get_positon().get_x() < mapWidth - 3)
            {
                if ((*it)->get_positon().get_y() == 0)
                    _shots.emplace_back(new SolShot((*it)->get_positon().get_x(), 1, SolDirection::Axis::DOWN, 3, 100, SolShot::Type::ENEMY));
                else
                    _shots.emplace_back(new SolShot((*it)->get_positon().get_x(), mapHeight - 2, SolDirection::Axis::UP, 3, 100, SolShot::Type::ENEMY));
            }
            else if (((*it)->get_direction().get_currentDir() == SolDirection::Axis::UP
                      || (*it)->get_direction().get_currentDir() == SolDirection::Axis::DOWN)
                     && (*it)->get_positon().get_y() > 2
                     && (*it)->get_positon().get_y() < mapHeight - 3)
            {
                if ((*it)->get_positon().get_x() == 0)
                    _shots.emplace_back(new SolShot(1, (*it)->get_positon().get_y(), SolDirection::Axis::RIGHT, 3, 100, SolShot::Type::ENEMY));
                else
                    _shots.emplace_back(new SolShot(mapWidth - 2, (*it)->get_positon().get_y(), SolDirection::Axis::LEFT, 3, 100, SolShot::Type::ENEMY));
            }
            (*it)->setTimeSinceLastShot();
        }
    }
}

void arcade::SolGame::playerControl() {
    double d;

    if (_player.isBoosted()) {
        d = dt * (_player.get_velocity() * 4);
        _player.setBoosted(false);
    }
    else
        d = dt * _player.get_velocity();
    _player.set_distance(_player.get_distance() + d);
    if (_player.get_distance() >= 1)
    {
        if (_player.get_direction().get_newDir() == SolDirection::Axis::LEFT) {
            _player.moveLeft();
            _player.set_currentDirection(SolDirection::Axis::LEFT);
        }
        if (_player.get_direction().get_newDir() == SolDirection::Axis::RIGHT) {
            _player.moveRight();
            _player.set_currentDirection(SolDirection::Axis::RIGHT);
        };
        if (_player.get_direction().get_newDir() == SolDirection::Axis::UP) {
            _player.moveUp();
            _player.set_currentDirection(SolDirection::Axis::UP);
        }
        if (_player.get_direction().get_newDir() == SolDirection::Axis::DOWN) {
            _player.moveDown();
            _player.set_currentDirection(SolDirection::Axis::DOWN);
        }
        _player.set_distance(0);
    }

    if (_player.is_fire()) {
        if (_player.get_direction().get_currentDir() == SolDirection::Axis::LEFT)
            _shots.emplace_back(
                    new SolShot(_player.get_positon().get_x() - 1, _player.get_positon().get_y(), SolDirection::Axis::LEFT,
                             20, 1, SolShot::Type::PLAYER));
        else if (_player.get_direction().get_currentDir() == SolDirection::Axis::RIGHT)
            _shots.emplace_back(
                    new SolShot(_player.get_positon().get_x() + 1, _player.get_positon().get_y(), SolDirection::Axis::RIGHT,
                             20, 1, SolShot::Type::PLAYER));
        else if (_player.get_direction().get_currentDir() == SolDirection::Axis::UP)
            _shots.emplace_back(
                    new SolShot(_player.get_positon().get_x(), _player.get_positon().get_y() - 1, SolDirection::Axis::UP, 20,
                             1, SolShot::Type::PLAYER));
        else if (_player.get_direction().get_currentDir() == SolDirection::Axis::DOWN)
            _shots.emplace_back(
                    new SolShot(_player.get_positon().get_x(), _player.get_positon().get_y() + 1, SolDirection::Axis::DOWN,
                             20, 1, SolShot::Type::PLAYER));
        _player.set_fire(false);
    }

    if (_map.getValue(_player.get_positon().get_x(), _player.get_positon().get_y()) != (int) Value::FREE
        && _map.getValue(_player.get_positon().get_x(), _player.get_positon().get_y()) != (int) Value::PLAYER
        && _map.getValue(_player.get_positon().get_x(), _player.get_positon().get_y()) != (int) Value::PLAYER_SHOT)
    {
        _state = IGame::State::OVER;
        return;
    }
}

void arcade::SolGame::shotControl() {
    std::vector<std::unique_ptr<SolShot>>::iterator it;

    shotCollision();
    for (it = _shots.begin(); it != _shots.end();)
    {
        if ((*it)->get_direction().get_currentDir() == SolDirection::Axis::LEFT
            && ((*it)->get_positon().get_x() <= 0 || (*it)->get_distRemaining() == 0))
            _shots.erase(it);
        else if ((*it)->get_direction().get_currentDir() == SolDirection::Axis::RIGHT
                 && ((*it)->get_positon().get_x() >= mapWidth - 1 || (*it)->get_distRemaining() == 0))
            _shots.erase(it);
        else if ((*it)->get_direction().get_currentDir() == SolDirection::Axis::UP
                 && ((*it)->get_positon().get_y() <= 0 || (*it)->get_distRemaining() == 0))
            _shots.erase(it);
        else if ((*it)->get_direction().get_currentDir() == SolDirection::Axis::DOWN
                 && ((*it)->get_positon().get_y() >= mapHeight - 1 || (*it)->get_distRemaining() == 0))
            _shots.erase(it);
        else
            ++it;
    }

    for (it = _shots.begin(); it != _shots.end(); ++it)
    {
        (*it)->set_distance((*it)->get_distance() + (dt * (*it)->get_velocity()));
        if ((*it)->get_distance() >= 1)
        {
            if ((*it)->get_direction().get_currentDir() == SolDirection::Axis::LEFT)
            {
                (*it)->moveLeft();
                (*it)->set_distRemaining((*it)->get_distRemaining() - 1);
            }
            else if ((*it)->get_direction().get_currentDir() == SolDirection::Axis::RIGHT)
            {
                (*it)->moveRight();
                (*it)->set_distRemaining((*it)->get_distRemaining() - 1);
            }
            else if ((*it)->get_direction().get_currentDir() == SolDirection::Axis::UP)
            {
                (*it)->moveUp();
                (*it)->set_distRemaining((*it)->get_distRemaining() - 1);
            }
            else if ((*it)->get_direction().get_currentDir() == SolDirection::Axis::DOWN)
            {
                (*it)->moveDown();
                (*it)->set_distRemaining((*it)->get_distRemaining() - 1);
            }
            (*it)->set_distance(0);
        }
    }
}

void arcade::SolGame::shotCollision() {
    std::vector<std::unique_ptr<SolShot>>::iterator    it;
    std::vector<std::pair<int, int>>::iterator      it2;
    std::vector<std::pair<int, int>>                shotCollisions;

    for (it = _shots.begin(); it != _shots.end(); ++it) {
        if ((*it)->get_typeShot() == SolShot::Type::PLAYER && inCollision((*it)->get_positon().get_x(), (*it)->get_positon().get_y()) == 1)
            shotCollisions.push_back(std::make_pair((*it)->get_positon().get_x(), (*it)->get_positon().get_y()));
    }
    for (it2 = shotCollisions.begin(); it2 != shotCollisions.end(); ++it2) {
        removeEntitiesInCollision((*it2).first, (*it2).second);
    }
}

bool arcade::SolGame::inCollision(int x, int y) {
    std::vector<std::unique_ptr<SolShot>>::iterator it;
    std::vector<std::unique_ptr<SolPowerUp>>::iterator it2;

    for (it = _shots.begin(); it != _shots.end(); ++it) {
        if ((*it)->get_typeShot() == SolShot::Type::ENEMY && (*it)->get_positon().get_x() == x && (*it)->get_positon().get_y() == y)
            return true;
    }
    for (it2 = _powerUps.begin(); it2 != _powerUps.end(); ++it2) {
        if ((*it2)->get_positon().get_x() == x && (*it2)->get_positon().get_y() == y)
            return true;
    }
    return false;
}

void arcade::SolGame::removeEntitiesInCollision(int x, int y) {
    std::vector<std::unique_ptr<SolShot>>::iterator it;
    std::vector<std::unique_ptr<SolPowerUp>>::iterator it2;

    for (it = _shots.begin(); it != _shots.end();) {
        if ((*it)->get_positon().get_x() == x && (*it)->get_positon().get_y() == y)
        {
            _shots.erase(it);
            _score += 2;
        }
        else
            ++it;
    }

    for (it2 = _powerUps.begin(); it2 != _powerUps.end();) {
        if ((*it2)->get_positon().get_x() == x && (*it2)->get_positon().get_y() == y)
        {
            _powerUps.erase(it2);
            _score += 1;
        }
        else
            ++it2;
    }
}

void arcade::SolGame::removeEntities() {
    std::vector<std::unique_ptr<SolEnemy>>::iterator it;
    std::vector<std::unique_ptr<SolShot>>::iterator it2;
    std::vector<std::unique_ptr<SolWall>>::iterator it3;
    std::vector<std::unique_ptr<SolPowerUp>>::iterator it4;

    for (it = _enemies.begin(); it != _enemies.end();)
        _enemies.erase(it);
    for (it3 = _walls.begin(); it3 != _walls.end();)
        _walls.erase(it3);
    for (it4 = _powerUps.begin(); it4 != _powerUps.end();)
        _powerUps.erase(it4);
    for (it2 = _shots.begin(); it2 != _shots.end();)
        _shots.erase(it2);
}

const std::string   &arcade::SolGame::getName() const {
    return _name;
}