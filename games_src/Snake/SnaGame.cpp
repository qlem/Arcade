//
// Created by pierre on 14/03/17.
//

#include <deque>
#include <iostream>
#include "SnaGame.hpp"

extern "C" arcade::SnaGame* create_object()
{
    return new arcade::SnaGame();
}

extern "C" void destroy_object(arcade::SnaGame* object)
{
    delete object;
}

arcade::SnaGame::SnaGame() :
        _state(State::RUN),
        _name("Snake")
{
    srand((unsigned int) time(nullptr));
    startNewGame();
}

arcade::SnaGame::~SnaGame() {}

void arcade::SnaGame::startNewGame() {
    std::vector<std::unique_ptr<SnaFood>>::iterator it1;
    std::vector<Event>::iterator it2;

    for (it1 = _food.begin(); it1 != _food.end();)
        _food.erase(it1);
    for (it2 = _events.begin(); it2 != _events.end();)
        _events.erase(it2);
    _state = State::RUN;
    _score.set_score(0);
    _map.initMap(mapWidth, mapHeight);
    _snake.resetTail();
    _snake.spawn(_map.getWidth(), _map.getHeight());
    _snake.set_velocity(3);
    _snake.set_boosted(false);
    _snake.set_distance(0.0);
    _direction.set_currentDir(SnaDirection::Axis::LEFT);
    _direction.set_newDir(SnaDirection::Axis::LEFT);
    initCoreMap();
    setEntitiesInMap();
    spawnNewFood();
    convertMap();
    _tStart = std::chrono::high_resolution_clock::now();
}

void    arcade::SnaGame::removeFood(int x, int y)
{
    std::vector<std::unique_ptr<SnaFood>>::iterator it;

    for (it = _food.begin(); it != _food.end(); ++it)
        if ((*it)->get_positon().get_x() == x && (*it)->get_positon().get_y() == y)
            _food.erase(it);
}

void    arcade::SnaGame::spawnNewFood()
{
    int x;
    int y;

    x = RAND(1, _map.getWidth() - 1);
    y = RAND(1, _map.getHeight() - 1);
    while (_map.getValue(x, y) != (int) Value::FREE) {
        x = RAND(1, _map.getWidth() - 1);
        y = RAND(1, _map.getHeight() - 1);
    }
    _food.emplace_back(new SnaFood(x , y));
}

bool arcade::SnaGame::checkIn(std::vector<arcade::IGame::Event> &_events, arcade::IGame::Event event)
{
    std::vector<Event>::iterator it;

    for(it = _events.begin(); it!=_events.end(); ++it)
        if (*it == event)
            return true;
    return false;
}

void arcade::SnaGame::saveEvent(arcade::IGame::Event event) {
    if (!checkIn(_events, event))
        _events.push_back(event);
}

void arcade::SnaGame::processEvent() {
    std::vector<Event>::iterator it;

    for(it = _events.begin(); it!=_events.end();)
        switch (*it)
        {
            case Event::UP:
                if (_direction.get_currentDir() != SnaDirection::Axis::DOWN)
                    _direction.set_newDir(SnaDirection::Axis::UP);
                if ((it =_events.erase(it)) == _events.end())
                    return;
                break;
            case Event::DOWN:
                if (_direction.get_currentDir() != SnaDirection::Axis::UP)
                    _direction.set_newDir(SnaDirection::Axis::DOWN);
                if ((it =_events.erase(it)) == _events.end())
                    return;
                break;
            case Event::RIGHT:
                if (_direction.get_currentDir() != SnaDirection::Axis::LEFT)
                    _direction.set_newDir(SnaDirection::Axis::RIGHT);
                if ((it =_events.erase(it)) == _events.end())
                    return;
                break;
            case Event::LEFT:
                if (_direction.get_currentDir() != SnaDirection::Axis::RIGHT)
                    _direction.set_newDir(SnaDirection::Axis::LEFT);
                if ((it =_events.erase(it)) == _events.end())
                    return;
                break;
            case Event::BOOST:
                _snake.set_boosted(true);
                if ((it =_events.erase(it)) == _events.end())
                    return;
                break;
            default:
                ++it;
                break;
        }
}

void arcade::SnaGame::update()
{
    processEvent();
    double d;
    SnaPos newTailPos;
    bool growUp = false;
    newTailPos = _snake.get_tail().back()->get_positon();

    if (_snake.is_boosted()) {
        d = dt * (_snake.get_velocity() * 4);
        _snake.set_boosted(false);
    }
    else
        d = dt * _snake.get_velocity();
    _snake.set_distance(_snake.get_distance() + d);
    if (_snake.get_distance() >= 1)
    {
        if (_direction.get_newDir() == SnaDirection::Axis::LEFT) {
            _snake.moveLeft();
            _direction.set_currentDir(SnaDirection::Axis::LEFT);
        }
        if (_direction.get_newDir() == SnaDirection::Axis::RIGHT) {
            _snake.moveRight();
            _direction.set_currentDir(SnaDirection::Axis::RIGHT);
        };
        if (_direction.get_newDir() == SnaDirection::Axis::UP) {
            _snake.moveUp();
            _direction.set_currentDir(SnaDirection::Axis::UP);
        }
        if (_direction.get_newDir() == SnaDirection::Axis::DOWN) {
            _snake.moveDown();
            _direction.set_currentDir(SnaDirection::Axis::DOWN);
        }
        _snake.set_distance(0);
    }

    std::vector<std::unique_ptr<SnaFood>>::iterator itFood;

    Value   newHeadPos = (Value) _map.getValue(_snake.get_head().get_positon().get_x(),
                                               _snake.get_head().get_positon().get_y());
    int     y = -1;
    int     x;

    if (newHeadPos == Value::TAILSCT || newHeadPos == Value::WALL) {
        _state = State::OVER;
        return;
    }

    //need to grow up if the snake's head is above a food
    if (newHeadPos == Value::FOOD) {
        growUp = true;
    }

    //write foods in the map
    for (itFood = _food.begin(); itFood != _food.end(); ++itFood)
        _map.setValue((*itFood)->get_positon().get_x(), (*itFood)->get_positon().get_y(), Value::FOOD);

    //remove in the map old snake
    while (++y < _map.getHeight()) {
        x = -1;
        while (++x < _map.getWidth()) {
            if (_map.getValue(x, y) == (int) Value::HEAD || _map.getValue(x, y) == (int) Value::TAILSCT)
                _map.setValue(x, y, Value::FREE);
        }
    }

    //write in the map new snake
    setEntitiesInMap();

    //try to grow up
    if (growUp) {
        if (_map.getValue(newTailPos.get_x(), newTailPos.get_y()) == (int) Value::FREE) {
            _snake.addNewTailSec(newTailPos);
            _score += 1;
            _snake.set_velocity(_snake.get_velocity() + 0.1);
            spawnNewFood();
            removeFood(_snake.get_head().get_positon().get_x(),
                       _snake.get_head().get_positon().get_y());
        }
        else
            _state = State::OVER;
    }
    convertMap();
}

const arcade::SnaMap &arcade::SnaGame::get_map() const {
    return _map;
}

char        **arcade::SnaGame::getMap() const {
    return _coreMap;
}

int arcade::SnaGame::getWidth() const {
    return get_map().getWidth();
}

int arcade::SnaGame::getHeight() const {
    return get_map().getHeight();
}

void        arcade::SnaGame::convertMap() {
    int     y = -1;
    int     x;

    while (++y < _map.getHeight()) {
        x = -1;
        while (++x < _map.getWidth()) {
            switch (_map.getValue(x, y)) {
                case (int) Value::WALL:
                    _coreMap[y][x] = (char) Color::LIGHTGRAY;
                    break;
                case (int) Value::HEAD:
                    _coreMap[y][x] = (char) Color::LIGHTGREEN;
                    break;
                case (int) Value::TAILSCT:
                    _coreMap[y][x] = (char) Color::GREEN;
                    break;
                case (int) Value::FOOD:
                    _coreMap[y][x] = (char) Color::MAGENTA;
                    break;
                case (int) Value::FREE:
                    _coreMap[y][x] = (char) Color::BLACK;
                    break;
                default:
                    break;
            }
        }
    }
}

void        arcade::SnaGame::initCoreMap() {
    _coreMap = new char*[mapHeight];
    for (auto n = 0; n < mapHeight; ++n)
        _coreMap[n] = new char[mapWidth];
}

arcade::IGame::State arcade::SnaGame::getState() const{
    return _state;
}

int arcade::SnaGame::getScore() const {
    return _score.get_score();
}

const std::string   &arcade::SnaGame::getName() const {
    return _name;
}

void arcade::SnaGame::setEntitiesInMap() {
    std::deque<std::unique_ptr<SnaTailSection>>::const_iterator it;
    std::vector<SnaFood>::iterator itFood;

    for (it = _snake.get_tail().begin(); it != _snake.get_tail().end(); ++it)
        _map.setValue((*it)->get_positon().get_x(), (*it)->get_positon().get_y(), Value::TAILSCT);
    _map.setValue(_snake.get_head().get_positon().get_x(),
                  _snake.get_head().get_positon().get_y(), Value::HEAD);
}