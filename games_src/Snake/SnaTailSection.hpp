//
// Created by pierre on 16/03/17.
//

#ifndef CPP_ARCADE_TAILSECTION_HPP
#define CPP_ARCADE_TAILSECTION_HPP

#include "SnaIEntity.hh"

namespace arcade {
    class SnaTailSection : public SnaIEntity
    {
    private:
        SnaPos                 _positon;
        Value               _value;
        bool                _plump;

    public:
        SnaTailSection();
        SnaTailSection(int x, int y);
        virtual ~SnaTailSection();
        void set_positon(int x, int y);
        void set_value(Value _value);
        const SnaPos &get_positon() const;
        const Value &get_value() const;
        bool is_plump() const;
        void set_plump(bool _plump);
    };
}

#endif //CPP_ARCADE_TAILSECTION_HPP
