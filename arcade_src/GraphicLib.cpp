//
// Created by raven57 on 07/04/17.
//

#include "GraphicLib.h"

arcade::GraphicLib::GraphicLib()
{

}

arcade::GraphicLib::GraphicLib(const std::string &fileName, IGraphic *graphicLib)
{
    this->name = fileName;
    this->graphicLib = graphicLib;
}

arcade::GraphicLib::~GraphicLib()
{

}

const std::string & arcade::GraphicLib::getName() const
{
    return (this->name);
}

arcade::IGraphic *arcade::GraphicLib::getGraphicLib() const
{
    return (this->graphicLib);
}