//
// Created by raven57 on 07/04/17.
//

#ifndef CPP_ARCADE_LIBLOADER_H
#define CPP_ARCADE_LIBLOADER_H

#include <dlfcn.h>
#include <string>

namespace arcade {

    class LibLoader {
    public:
        LibLoader();
        ~LibLoader();
        void *openLib(const std::string &library) const;
        void *loadSymbol(void *lib, const std::string &symbol) const;
        void closeLib(void *lib) const;
    };

}

#endif //CPP_ARCADE_LIBLOADER_H
