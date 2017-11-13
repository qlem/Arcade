//
// Created by dommer_c on 24/03/17.
//

#ifndef CPP_ARCADE_USER_INTERFACE_H
#define CPP_ARCADE_USER_INTERFACE_H

#include <vector>
#include <string>

namespace arcade {
    class IGraphic {
    public:
        enum class Key {
            KEY_UP,
            KEY_DOWN,
            KEY_RIGHT,
            KEY_LEFT,
            KEY_SPACE,
            KEY_0,
            KEY_1,
            KEY_2,
            KEY_3,
            KEY_4,
            KEY_5,
            KEY_6,
            KEY_7,
            KEY_8,
            KEY_9,
            KEY_ESCAPE,
            KEY_QUIT,
            KEY_A,
            KEY_B,
            KEY_C,
            KEY_D,
            KEY_E,
            KEY_F,
            KEY_G,
            KEY_H,
            KEY_I,
            KEY_J,
            KEY_K,
            KEY_L,
            KEY_M,
            KEY_N,
            KEY_O,
            KEY_P,
            KEY_Q,
            KEY_R,
            KEY_S,
            KEY_T,
            KEY_U,
            KEY_V,
            KEY_W,
            KEY_X,
            KEY_Y,
            KEY_Z,
            KEY_ENTER,
            KEY_TAB,
            KEY_UNDEFINED,
            KEY_DELETE
        };

        enum class Color {
            WHITE,
            LIGHTGRAY,
            DARKGRAY,
            BLACK,
            BROWN,
            LIGHTRED,
            RED,
            YELLOW,
            LIGHTGREEN,
            GREEN,
            LIGHTBLUE,
            LIGHTCYAN,
            BLUE,
            LIGHTMAGENTA,
            MAGENTA,
            CYAN
        };

        enum class Style {
            BOLD,
            ITALICS,
            UNDERLINE,
            BLINK,
            STRIKE,
            REGULAR
        };

    public:
        virtual void                    createDisplay(int width, int height) = 0;
        virtual void                    draw(int x, int y, Color color) = 0;
        virtual void                    destroyDisplay() = 0;
        virtual void                    refreshDisplay() = 0;
        virtual void                    catchInput(std::vector<Key> &_events) = 0;
        virtual void                    clearDisplay() = 0;
        virtual void                    writeText(int x, int y, const std::string &str, Color color, Style style) = 0;
        virtual const std::string       &getName() const = 0;
        virtual void                    resizeDisplay(int x, int y) = 0;
        virtual const std::pair<int, int>   getDisplaySize() const = 0;
        virtual const std::string       &getTextEntered() const = 0;
        virtual void                    setTextEntryMod(bool mod) = 0;
        virtual bool                    getTextEntryMod() const = 0;
    };
}

#endif //CPP_ARCADE_USER_INTERFACE_H
