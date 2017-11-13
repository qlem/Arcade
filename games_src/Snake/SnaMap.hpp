//
// Created by pierre on 08/03/17.
//

#ifndef CPP_ARCADE_MAP_HPP
#define CPP_ARCADE_MAP_HPP

namespace arcade {
    enum class Value : int
    {
        HEAD,
        FOOD,
        WALL,
        TAILSCT,
        FREE
    };

    class SnaMap
    {
    private:
        int       _width;
        int       _height;
        char      **_map;

    public:
        SnaMap();
        virtual ~SnaMap();
        int             getWidth() const;
        int             getHeight() const;
        int             getValue(const int x, const int y) const;
        void            setValue(const int x, const int y, Value n);
        void            initMap(int x, int y);
        void            set_width(int _width);
        void            set_height(int _height);
        char             **get_map() const;
    };
}

#endif //CPP_ARCADE_MAP_HPP