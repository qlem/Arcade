//
// Created by raven57 on 07/04/17.
//

#ifndef CPP_ARCADE_GRAPHICLIB_H
#define CPP_ARCADE_GRAPHICLIB_H

#include <string>
#include "../inc/IGraphic.hh"

namespace arcade {

    class GraphicLib {
    private:
        std::string name = "";
        IGraphic *graphicLib = NULL;

    public:
        GraphicLib();
        GraphicLib(const std::string &fileName, IGraphic *graphicLib);
        ~GraphicLib();
        const std::string &getName() const;
        IGraphic *getGraphicLib() const;
    };

}
#endif //CPP_ARCADE_GRAPHICLIB_H
