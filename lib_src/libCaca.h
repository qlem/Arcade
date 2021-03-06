//
// Created by dommer_c on 27/03/17.
//

#ifndef CPP_ARCADE_LIBCACA_H
#define CPP_ARCADE_LIBCACA_H

#include <caca.h>
#include "../inc/IGraphic.hh"

namespace arcade {

    class libCaca : arcade::IGraphic {
    private:
        caca_canvas_t         *_cv;
        caca_display_t        *_dp;
        caca_event_t          _ev;
        std::string           _name;
        bool                  _inputMod;
        std::string           _buffer;
    public:
        libCaca();
        virtual ~libCaca();

        void    createDisplay(int width, int height);
        void    draw(int x, int y, Color color);
        void    destroyDisplay(void);
        void    refreshDisplay(void);
        void    clearDisplay(void);
        void    catchInput(std::vector<Key> &events);
        const   std::string &getName() const;
        void    writeText(int x, int y, const std::string &str, Color color, Style style);
        void    resizeDisplay(int x, int y);
        const std::string       &getTextEntered() const;
        void    setTextEntryMod(bool mod);
        bool    getTextEntryMod() const;
        const   std::pair<int, int>   getDisplaySize() const;


        void addEvent(std::vector<arcade::IGraphic::Key> &events, arcade::IGraphic::Key key);
        void deleteEvent(std::vector<arcade::IGraphic::Key> &events, arcade::IGraphic::Key key);
        caca_color translateColor(arcade::IGraphic::Color color);
    };

}

#endif //CPP_ARCADE_LIBCACA_H
