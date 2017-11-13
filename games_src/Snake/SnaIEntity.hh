//
// Created by pierre on 09/03/17.
//

#ifndef CPP_ARCADE_IENTITY_HH
#define CPP_ARCADE_IENTITY_HH

#include "SnaMap.hpp"
#include "SnaPos.hpp"

namespace arcade {
    class SnaIEntity
    {
        virtual const SnaPos &get_positon() const = 0;
        virtual const Value &get_value() const = 0;
    };
}

#endif //CPP_ARCADE_IENTITY_HH
