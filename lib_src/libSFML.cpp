//
// Created by dommer_c on 27/03/17.
//

#include "libSFML.h"

extern "C" arcade::libSFML* create_object()
{
    return new arcade::libSFML;
}

extern "C" void destroy_object(arcade::libSFML* object)
{
    delete object;
}


arcade::libSFML::libSFML() {
    this->_name = "SFML";
    this->_inputMod = false;
}

arcade::libSFML::~libSFML() {

}

void arcade::libSFML::draw(int x, int y, Color color)
{
    sf::RectangleShape square(sf::Vector2f(BOX_SIZE, BOX_SIZE));
    square.setPosition(x * BOX_SIZE, y * BOX_SIZE);
    square.setFillColor(this->translateColor(color));
    this->_window.draw(square);
}

void arcade::libSFML::createDisplay(int width, int height) {
    this->_window.create(sf::VideoMode((unsigned int)width * BOX_SIZE, (unsigned int)height * BOX_SIZE), "ARCADE");
}

void arcade::libSFML::destroyDisplay(void) {
    this->_window.close();
}

void arcade::libSFML::refreshDisplay(void) {
    this->_window.display();
}

void arcade::libSFML::catchInput(std::vector<Key> &events) {
    while (this->_window.pollEvent(this->_event)) {

        switch (this->_event.type) {

            case sf::Event::Closed:
                addEvent(events, arcade::IGraphic::Key::KEY_QUIT);
                break;

            case sf::Event::KeyPressed :
                    switch (this->_event.key.code) {
                        case sf::Keyboard::Left :
                            addEvent(events, arcade::IGraphic::Key::KEY_LEFT);
                            break;
                        case sf::Keyboard::Right :
                            addEvent(events, arcade::IGraphic::Key::KEY_RIGHT);
                            break;
                        case sf::Keyboard::Up :
                            addEvent(events, arcade::IGraphic::Key::KEY_UP);
                            break;
                        case sf::Keyboard::Down :
                            addEvent(events, arcade::IGraphic::Key::KEY_DOWN);
                            break;
                        case sf::Keyboard::Escape :
                            addEvent(events, arcade::IGraphic::Key::KEY_ESCAPE);
                            break;
                        case sf::Keyboard::Space :
                            addEvent(events, arcade::IGraphic::Key::KEY_SPACE);
                            break;
                        case sf::Keyboard::A :
                            if (!this->_inputMod)
                                addEvent(events, arcade::IGraphic::Key::KEY_A);
                            break;
                        case sf::Keyboard::B :
                            addEvent(events, arcade::IGraphic::Key::KEY_B);
                            break;
                        case sf::Keyboard::C :
                            addEvent(events, arcade::IGraphic::Key::KEY_C);
                            break;
                        case sf::Keyboard::D :
                            addEvent(events, arcade::IGraphic::Key::KEY_D);
                            break;
                        case sf::Keyboard::E :
                           addEvent(events, arcade::IGraphic::Key::KEY_E);
                            break;
                        case sf::Keyboard::F :
                           addEvent(events, arcade::IGraphic::Key::KEY_F);
                            break;
                        case sf::Keyboard::G :
                           addEvent(events, arcade::IGraphic::Key::KEY_G);
                            break;
                        case sf::Keyboard::H :
                            addEvent(events, arcade::IGraphic::Key::KEY_H);
                            break;
                        case sf::Keyboard::I :
                           addEvent(events, arcade::IGraphic::Key::KEY_I);
                            break;
                        case sf::Keyboard::J :
                            addEvent(events, arcade::IGraphic::Key::KEY_J);
                            break;
                        case sf::Keyboard::K :
                            addEvent(events, arcade::IGraphic::Key::KEY_K);
                            break;
                        case sf::Keyboard::L :
                            addEvent(events, arcade::IGraphic::Key::KEY_L);
                            break;
                        case sf::Keyboard::M :
                            addEvent(events, arcade::IGraphic::Key::KEY_M);
                            break;
                        case sf::Keyboard::N :
                            addEvent(events, arcade::IGraphic::Key::KEY_N);
                            break;
                        case sf::Keyboard::O :
                            addEvent(events, arcade::IGraphic::Key::KEY_O);
                            break;
                        case sf::Keyboard::P :
                            addEvent(events, arcade::IGraphic::Key::KEY_P);
                            break;
                        case sf::Keyboard::Q :
                            if (!this->_inputMod)
                                addEvent(events, arcade::IGraphic::Key::KEY_Q);
                            break;
                        case sf::Keyboard::R :
                            if (!this->_inputMod)
                                addEvent(events, arcade::IGraphic::Key::KEY_R);
                            break;
                        case sf::Keyboard::S :
                            if (!this->_inputMod)
                                addEvent(events, arcade::IGraphic::Key::KEY_S);
                            break;
                        case sf::Keyboard::T :
                            addEvent(events, arcade::IGraphic::Key::KEY_T);
                            break;
                        case sf::Keyboard::U :
                            addEvent(events, arcade::IGraphic::Key::KEY_U);
                            break;
                        case sf::Keyboard::V :
                            addEvent(events, arcade::IGraphic::Key::KEY_V);
                            break;
                        case sf::Keyboard::W :
                            addEvent(events, arcade::IGraphic::Key::KEY_W);
                            break;
                        case sf::Keyboard::X :
                            addEvent(events, arcade::IGraphic::Key::KEY_X);
                            break;
                        case sf::Keyboard::Y :
                            addEvent(events, arcade::IGraphic::Key::KEY_Y);
                            break;
                        case sf::Keyboard::Z :
                            if (!this->_inputMod)
                                addEvent(events, arcade::IGraphic::Key::KEY_Z);
                            break;
                        case sf::Keyboard::Num0 :
                            addEvent(events, arcade::IGraphic::Key::KEY_0);
                            break;
                        case sf::Keyboard::Num1 :
                            addEvent(events, arcade::IGraphic::Key::KEY_1);
                            break;
                        case sf::Keyboard::Num2 :
                            addEvent(events, arcade::IGraphic::Key::KEY_2);
                            break;
                        case sf::Keyboard::Num3 :
                            addEvent(events, arcade::IGraphic::Key::KEY_3);
                            break;
                        case sf::Keyboard::Num4 :
                            addEvent(events, arcade::IGraphic::Key::KEY_4);
                            break;
                        case sf::Keyboard::Num5 :
                            addEvent(events, arcade::IGraphic::Key::KEY_5);
                            break;
                        case sf::Keyboard::Num6 :
                            addEvent(events, arcade::IGraphic::Key::KEY_6);
                            break;
                        case sf::Keyboard::Num7 :
                            addEvent(events, arcade::IGraphic::Key::KEY_7);
                            break;
                        case sf::Keyboard::Num8 :
                            addEvent(events, arcade::IGraphic::Key::KEY_8);
                            break;
                        case sf::Keyboard::Num9 :
                            addEvent(events, arcade::IGraphic::Key::KEY_9);
                            break;
                        case sf::Keyboard::Return :
                            addEvent(events, arcade::IGraphic::Key::KEY_ENTER);
                            break;
                        case sf::Keyboard::BackSpace :
                            if (this->_inputMod && this->_buffer.size())
                                this->_buffer.pop_back();
                            break;
                        default:
                            break;
                    }
                break;

            case sf::Event::KeyReleased :
                switch (this->_event.key.code) {
                    case sf::Keyboard::Left :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_LEFT);
                        break;
                    case sf::Keyboard::Right :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_RIGHT);
                        break;
                    case sf::Keyboard::Up :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_UP);
                        break;
                    case sf::Keyboard::Down :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_DOWN);
                        break;
                    case sf::Keyboard::Escape :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_ESCAPE);
                        break;
                    case sf::Keyboard::Space :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_SPACE);
                        break;
                    case sf::Keyboard::A :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_A);
                        break;
                    case sf::Keyboard::B :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_B);
                        break;
                    case sf::Keyboard::C :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_C);
                        break;
                    case sf::Keyboard::D :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_D);
                        break;
                    case sf::Keyboard::E :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_E);
                        break;
                    case sf::Keyboard::F :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_F);
                        break;
                    case sf::Keyboard::G :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_G);
                        break;
                    case sf::Keyboard::H :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_H);
                        break;
                    case sf::Keyboard::I :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_I);
                        break;
                    case sf::Keyboard::J :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_J);
                        break;
                    case sf::Keyboard::K :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_K);
                        break;
                    case sf::Keyboard::L :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_L);
                        break;
                    case sf::Keyboard::M :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_M);
                        break;
                    case sf::Keyboard::N :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_N);
                        break;
                    case sf::Keyboard::O :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_O);
                        break;
                    case sf::Keyboard::P :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_P);
                        break;
                    case sf::Keyboard::Q :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_Q);
                        break;
                    case sf::Keyboard::R :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_R);
                        break;
                    case sf::Keyboard::S :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_S);
                        break;
                    case sf::Keyboard::T :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_T);
                        break;
                    case sf::Keyboard::U :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_U);
                        break;
                    case sf::Keyboard::V :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_V);
                        break;
                    case sf::Keyboard::W :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_W);
                        break;
                    case sf::Keyboard::X :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_X);
                        break;
                    case sf::Keyboard::Y :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_Y);
                        break;
                    case sf::Keyboard::Z :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_Z);
                        break;
                    case sf::Keyboard::Num0 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_0);
                        break;
                    case sf::Keyboard::Num1 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_1);
                        break;
                    case sf::Keyboard::Num2 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_2);
                        break;
                    case sf::Keyboard::Num3 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_3);
                        break;
                    case sf::Keyboard::Num4 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_4);
                        break;
                    case sf::Keyboard::Num5 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_5);
                        break;
                    case sf::Keyboard::Num6 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_6);
                        break;
                    case sf::Keyboard::Num7 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_7);
                        break;
                    case sf::Keyboard::Num8 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_8);
                        break;
                    case sf::Keyboard::Num9 :
                        deleteEvent(events, arcade::IGraphic::Key::KEY_9);
                        break;
                    default:
                        break;
                }
                break;

            case sf::Event::TextEntered :
                if (this->_inputMod && this->_event.text.unicode > 96 && this->_event.text.unicode < 123 && this->_buffer.size() < 3)
                    this->_buffer += this->_event.text.unicode - 32;
                break;

            default:
                break;
        }
    }
}

void arcade::libSFML::clearDisplay(void) {
    this->_window.clear(sf::Color::Black);
}

void arcade::libSFML::addEvent(std::vector<arcade::IGraphic::Key> &events, arcade::IGraphic::Key key) {
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

void arcade::libSFML::deleteEvent(std::vector<arcade::IGraphic::Key> &events, arcade::IGraphic::Key key) {
    std::vector<arcade::IGraphic::Key>::iterator     it;

    for (it = events.begin(); it != events.end();) {
        if (*it == key)
            it = events.erase(it);
        else
            it++;
    }
}

const std::string &arcade::libSFML::getName() const {
    return this->_name;
}

void arcade::libSFML::writeText(int x, int y, const std::string &str, arcade::IGraphic::Color color, arcade::IGraphic::Style style) {
    sf::Text text;
    sf::Font font;

    (void)style;
    font.loadFromFile("lib_src/ARCADE_I.TTF");
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(16);
    text.setFillColor(this->translateColor(color));
    text.setPosition(x * BOX_SIZE, y * BOX_SIZE);
    this->_window.draw(text);
}

sf::Color arcade::libSFML::translateColor(arcade::IGraphic::Color color) {
    sf::Color colorSFML;

    switch (color) {
        case arcade::IGraphic::Color::WHITE :
            colorSFML = sf::Color::White;
            break;
        case arcade::IGraphic::Color::LIGHTGRAY :
            colorSFML = sf::Color(180, 180, 180);
            break;
        case arcade::IGraphic::Color::DARKGRAY :
            colorSFML = sf::Color(80, 80, 80);
            break;
        case arcade::IGraphic::Color::BLACK :
            colorSFML = sf::Color::Black;
            break;
        case arcade::IGraphic::Color::BROWN :
            colorSFML = sf::Color(139,69,19);
            break;
        case arcade::IGraphic::Color::LIGHTRED :
            colorSFML = sf::Color(255, 130, 130);
            break;
        case arcade::IGraphic::Color::RED :
            colorSFML = sf::Color::Red;
            break;
        case arcade::IGraphic::Color::YELLOW :
            colorSFML = sf::Color::Yellow;
            break;
        case arcade::IGraphic::Color::LIGHTGREEN :
            colorSFML = sf::Color(132, 255, 134);
            break;
        case arcade::IGraphic::Color::GREEN :
            colorSFML = sf::Color::Green;
            break;
        case arcade::IGraphic::Color::LIGHTBLUE :
            colorSFML = sf::Color(119, 194, 255);
            break;
        case arcade::IGraphic::Color::LIGHTCYAN :
            colorSFML = sf::Color(119, 255, 252);
            break;
        case arcade::IGraphic::Color::BLUE :
            colorSFML = sf::Color::Blue;
            break;
        case arcade::IGraphic::Color::LIGHTMAGENTA :
            colorSFML = sf::Color(237, 83, 147);
            break;
        case arcade::IGraphic::Color::MAGENTA :
            colorSFML = sf::Color::Magenta;
            break;
        case arcade::IGraphic::Color::CYAN :
            colorSFML = sf::Color::Cyan;
            break;
    }
    return colorSFML;
}

void arcade::libSFML::resizeDisplay(int x, int y) {
    unsigned int     width;
    unsigned int     height;

    width = (unsigned int) (x * BOX_SIZE);
    height = (unsigned int) (y * BOX_SIZE);
    this->_window.setSize(sf::Vector2u(width, height));
    sf::FloatRect visibleArea(0, 0, width, height);
    this->_window.setView(sf::View(visibleArea));
}

const std::string &arcade::libSFML::getTextEntered() const {
    return this->_buffer;
}

void arcade::libSFML::setTextEntryMod(bool mod) {
    this->_inputMod = mod;
}

bool arcade::libSFML::getTextEntryMod() const {
    return this->_inputMod;
}

const std::pair<int, int> arcade::libSFML::getDisplaySize() const {
    return std::make_pair(0, 0);
}


