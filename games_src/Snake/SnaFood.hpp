//
// Created by pierre on 21/03/17.
//

#ifndef CPP_ARCADE_FOOD_HPP
#define CPP_ARCADE_FOOD_HPP

#include "SnaIEntity.hh"

namespace arcade {
    class SnaFood : public SnaIEntity
    {
    private:
        SnaPos                 _positon;
        Value               _value;

    public:
        SnaFood(int x, int y);
        SnaFood();
        virtual ~SnaFood();
        const SnaPos &get_positon() const;
        void set_positon(int x, int y);
        const Value &get_value() const;
        void set_value(Value _value);
    };
}

#endif //CPP_ARCADE_FOOD_HPP
