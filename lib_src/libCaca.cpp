//
// Created by dommer_c on 27/03/17.
//

#include "libCaca.h"

extern "C" arcade::libCaca* create_object()
{
    return new arcade::libCaca;
}

extern "C" void destroy_object(arcade::libCaca* object)
{
    delete object;
}

arcade::libCaca::libCaca() {
    this->_name = "Caca";
    this->_inputMod = false;
}

void arcade::libCaca::createDisplay(int width, int height) {
    this->_cv = caca_create_canvas(width * 2, height);
    this->_dp = caca_create_display(this->_cv);
    caca_set_display_title(this->_dp, "ARCADE");
}

void arcade::libCaca::destroyDisplay(void) {
    caca_free_display(this->_dp);
    caca_free_canvas(this->_cv);
}

void arcade::libCaca::draw(int x, int y, Color color)
{
    x *= 2;
    caca_set_color_ansi(this->_cv, CACA_BLACK, this->translateColor(color));
    caca_put_str(this->_cv, x, y, "  ");
}

void arcade::libCaca::refreshDisplay(void) {
    caca_refresh_display(this->_dp);
}

arcade::libCaca::~libCaca() {
    this->_inputMod = false;
}

void arcade::libCaca::catchInput(std::vector<Key> &events) {
    caca_get_event(this->_dp, CACA_EVENT_KEY_PRESS | CACA_EVENT_KEY_RELEASE | CACA_EVENT_QUIT, &this->_ev, 1);

    switch (caca_get_event_type(&this->_ev)) {

        case CACA_EVENT_QUIT:
            addEvent(events, arcade::IGraphic::Key::KEY_QUIT);
            break;

        case CACA_EVENT_KEY_PRESS :
            switch (caca_get_event_key_ch(&this->_ev)) {
                case CACA_KEY_LEFT :
                    addEvent(events, arcade::IGraphic::Key::KEY_LEFT);
                    break;
                case CACA_KEY_RIGHT :
                    addEvent(events, arcade::IGraphic::Key::KEY_RIGHT);
                    break;
                case CACA_KEY_UP :
                    addEvent(events, arcade::IGraphic::Key::KEY_UP);
                    break;
                case CACA_KEY_DOWN :
                    addEvent(events, arcade::IGraphic::Key::KEY_DOWN);
                    break;
                case ' ' :
                    addEvent(events, arcade::IGraphic::Key::KEY_SPACE);
                    break;
                case 'a' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)
                        addEvent(events, arcade::IGraphic::Key::KEY_A);
                    break;
                case 'b' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)
                        addEvent(events, arcade::IGraphic::Key::KEY_B);
                    break;
                case 'c' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_C);
                    break;
                case 'd' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_D);
                    break;
                case 'e' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_E);
                    break;
                case 'f' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_F);
                    break;
                case 'g' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_G);
                    break;
                case 'h' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_H);
                    break;
                case 'i' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_I);
                    break;
                case 'j' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_J);
                    break;
                case 'k' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_K);
                    break;
                case 'l' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_L);
                    break;
                case 'm' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_M);
                    break;
                case 'n' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_N);
                    break;
                case 'o' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_O);
                    break;
                case 'p' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_P);
                    break;
                case 'q' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)
                        addEvent(events, arcade::IGraphic::Key::KEY_Q);
                    break;
                case 'r' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)
                        addEvent(events, arcade::IGraphic::Key::KEY_R);
                    break;
                case 's' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)
                        addEvent(events, arcade::IGraphic::Key::KEY_S);
                    break;
                case 't' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_T);
                    break;
                case 'u' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_U);
                    break;
                case 'v' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_V);
                    break;
                case 'w' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_W);
                    break;
                case 'x' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_X);
                    break;
                case 'y' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)

                        addEvent(events, arcade::IGraphic::Key::KEY_Y);
                    break;
                case 'z' :
                    if (this->_inputMod && this->_buffer.size() < 3)
                        this->_buffer.push_back((char) ((char) caca_get_event_key_utf32(&this->_ev) - 32));
                    else if (!this->_inputMod)
                        addEvent(events, arcade::IGraphic::Key::KEY_Z);
                    break;
                case '0' :
                    addEvent(events, arcade::IGraphic::Key::KEY_0);
                    break;
                case '1' :
                    addEvent(events, arcade::IGraphic::Key::KEY_1);
                    break;
                case '2' :
                    addEvent(events, arcade::IGraphic::Key::KEY_2);
                    break;
                case '3' :
                    addEvent(events, arcade::IGraphic::Key::KEY_3);
                    break;
                case '4' :
                    addEvent(events, arcade::IGraphic::Key::KEY_4);
                    break;
                case '5' :
                    addEvent(events, arcade::IGraphic::Key::KEY_5);
                    break;
                case '6' :
                    addEvent(events, arcade::IGraphic::Key::KEY_6);
                    break;
                case '7' :
                    addEvent(events, arcade::IGraphic::Key::KEY_7);
                    break;
                case '8' :
                    addEvent(events, arcade::IGraphic::Key::KEY_8);
                    break;
                case '9' :
                    addEvent(events, arcade::IGraphic::Key::KEY_9);
                    break;
                case CACA_KEY_RETURN :
                    addEvent(events, arcade::IGraphic::Key::KEY_ENTER);
                    break;
                case 27 :
                    addEvent(events, arcade::IGraphic::Key::KEY_ESCAPE);
                    break;
                case CACA_KEY_BACKSPACE:
                    if (this->_inputMod && !this->_buffer.empty())
                        this->_buffer.pop_back();
                    break;
                default :
                    break;
            }
            break;

        case CACA_EVENT_KEY_RELEASE:
            switch (caca_get_event_key_ch(&this->_ev)) {
                case CACA_KEY_LEFT :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_LEFT);
                    break;
                case CACA_KEY_RIGHT :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_RIGHT);
                    break;
                case CACA_KEY_UP :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_UP);
                    break;
                case CACA_KEY_DOWN :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_DOWN);
                    break;
                case ' ' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_SPACE);
                    break;
                case 'a' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_A);
                    break;
                case 'b' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_B);
                    break;
                case 'c' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_C);
                    break;
                case 'd' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_D);
                    break;
                case 'e' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_E);
                    break;
                case 'f' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_F);
                    break;
                case 'g' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_G);
                    break;
                case 'h' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_H);
                    break;
                case 'i' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_I);
                    break;
                case 'j' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_J);
                    break;
                case 'k' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_K);
                    break;
                case 'l' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_L);
                    break;
                case 'm' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_M);
                    break;
                case 'n' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_N);
                    break;
                case 'o' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_O);
                    break;
                case 'p' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_P);
                    break;
                case 'q' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_Q);
                    break;
                case 'r' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_R);
                    break;
                case 's' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_S);
                    break;
                case 't' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_T);
                    break;
                case 'u' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_U);
                    break;
                case 'v' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_V);
                    break;
                case 'w' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_W);
                    break;
                case 'x' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_X);
                    break;
                case 'y' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_Y);
                    break;
                case 'z' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_Z);
                    break;
                case '0' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_0);
                    break;
                case '1' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_1);
                    break;
                case '2' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_2);
                    break;
                case '3' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_3);
                    break;
                case '4' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_4);
                    break;
                case '5' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_5);
                    break;
                case '6' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_6);
                    break;
                case '7' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_7);
                    break;
                case '8' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_8);
                    break;
                case '9' :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_9);
                    break;
                case CACA_KEY_RETURN :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_ENTER);
                    break;
                case 27 :
                    deleteEvent(events, arcade::IGraphic::Key::KEY_ESCAPE);
                    break;
                default :
                    break;
            }
            break;

        default:
            break;
    }
}

void arcade::libCaca::addEvent(std::vector<arcade::IGraphic::Key> &events, arcade::IGraphic::Key key) {
    std::vector<arcade::IGraphic::Key>::iterator     it;
    bool    check;

    check = false;
    for (it = events.begin(); it != events.end(); it++) {
        if (*it == key)
            check = true;
    }
    if (!check)
        events.push_back(key);
}

void arcade::libCaca::deleteEvent(std::vector<arcade::IGraphic::Key> &events, arcade::IGraphic::Key key) {
    std::vector<arcade::IGraphic::Key>::iterator     it;

    for (it = events.begin(); it != events.end();) {
        if (*it == key)
            it = events.erase(it);
        else
            it++;
    }
}

void arcade::libCaca::clearDisplay(void) {
    caca_clear_canvas(this->_cv);
}

void arcade::libCaca::writeText(int x, int y, const std::string &str, arcade::IGraphic::Color color, arcade::IGraphic::Style style) {
    (void)style;
    caca_set_color_ansi(_cv, translateColor(color), CACA_BLACK);
    caca_put_str(_cv, x * 2, y, str.c_str());
}

const std::string &arcade::libCaca::getName() const {
    return this->_name;
}

caca_color arcade::libCaca::translateColor(arcade::IGraphic::Color color) {
    caca_color  colorCaca;

    switch (color) {
        case arcade::IGraphic::Color::WHITE :
            colorCaca = CACA_WHITE;
            break;
        case arcade::IGraphic::Color::LIGHTGRAY :
            colorCaca = CACA_LIGHTGRAY;
            break;
        case arcade::IGraphic::Color::DARKGRAY :
            colorCaca = CACA_DARKGRAY;
            break;
        case arcade::IGraphic::Color::BLACK :
            colorCaca = CACA_BLACK;
            break;
        case arcade::IGraphic::Color::BROWN :
            colorCaca = CACA_BROWN;
            break;
        case arcade::IGraphic::Color::LIGHTRED :
            colorCaca = CACA_LIGHTRED;
            break;
        case arcade::IGraphic::Color::RED :
            colorCaca = CACA_RED;
            break;
        case arcade::IGraphic::Color::YELLOW :
            colorCaca = CACA_YELLOW;
            break;
        case arcade::IGraphic::Color::LIGHTGREEN :
            colorCaca = CACA_LIGHTGREEN;
            break;
        case arcade::IGraphic::Color::GREEN :
            colorCaca = CACA_GREEN;
            break;
        case arcade::IGraphic::Color::LIGHTBLUE :
            colorCaca = CACA_LIGHTBLUE;
            break;
        case arcade::IGraphic::Color::LIGHTCYAN :
            colorCaca = CACA_LIGHTCYAN;
            break;
        case arcade::IGraphic::Color::BLUE :
            colorCaca = CACA_BLUE;
            break;
        case arcade::IGraphic::Color::LIGHTMAGENTA :
            colorCaca = CACA_LIGHTMAGENTA;
            break;
        case arcade::IGraphic::Color::MAGENTA :
            colorCaca = CACA_MAGENTA;
            break;
        case arcade::IGraphic::Color::CYAN :
            colorCaca = CACA_CYAN;
            break;
    }
    return colorCaca;
}

void arcade::libCaca::resizeDisplay(int x, int y) {
    this->clearDisplay();
    caca_set_canvas_size(this->_cv, x, y);
    this->destroyDisplay();
    this->createDisplay(x, y);
}

const std::string &arcade::libCaca::getTextEntered() const {
    return this->_buffer;
}

void arcade::libCaca::setTextEntryMod(bool mod) {
    this->_inputMod = mod;
}

bool arcade::libCaca::getTextEntryMod() const {
    return this->_inputMod;
}

const std::pair<int, int> arcade::libCaca::getDisplaySize() const {
    return std::make_pair(0, 0);
}
