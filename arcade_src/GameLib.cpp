//
// Created by raven57 on 07/04/17.
//

#include "GameLib.h"

arcade::GameLib::GameLib()
{

}

arcade::GameLib::GameLib(const std::string &fileName, IGame *graphicLib)
{
    this->name = fileName;
    this->gameLib = graphicLib;
}

arcade::GameLib::~GameLib()
{

}

const std::string & arcade::GameLib::getName() const
{
    return (this->name);
}

arcade::IGame *arcade::GameLib::getGameLib() const
{
    return (this->gameLib);
}