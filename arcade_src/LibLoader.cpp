//
// Created by raven57 on 07/04/17.
//

#include "LibLoader.h"

arcade::LibLoader::LibLoader()
{

}

arcade::LibLoader::~LibLoader()
{

}

void *arcade::LibLoader::openLib(const std::string &library) const
{
    return dlopen(library.c_str(), RTLD_LAZY);
}

void *arcade::LibLoader::loadSymbol(void *lib, const std::string &symbol) const
{
    return dlsym(lib, symbol.c_str());
}

void arcade::LibLoader::closeLib(void *lib) const
{
    dlclose(lib);
}
