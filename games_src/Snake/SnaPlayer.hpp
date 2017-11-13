//
// Created by pierre on 10/03/17.
//

#ifndef CPP_ARCADE_PLAYER_HPP
#define CPP_ARCADE_PLAYER_HPP

#include "SnaMap.hpp"
#include "SnaIEntity.hh"

namespace arcade {
    class SnaPlayer : public SnaIEntity
    {
    private:
        SnaPos                 _positon;
        Value               _value;

    public:
        SnaPlayer();
        virtual ~SnaPlayer();
        void set_positon(int x, int y);
        void set_value(Value _value);
        const SnaPos &get_positon() const;
        const Value &get_value() const;
    };
}

#endif //CPP_ARCADE_PLAYER_HPP