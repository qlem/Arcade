//
// Created by dommer_c on 17/04/17.
//

#ifndef CPP_ARCADE_SCORE_H
#define CPP_ARCADE_SCORE_H

#include <fstream>
#include <vector>
#include <algorithm>

namespace arcade {

    class Scoring {

    private:
        std::vector<std::pair<std::string, int>>   _scores;

    public:
        void    saveScore(const std::string &game, const std::string &playerName, const int &score);
        std::vector<std::pair<std::string, int>> &getScores(const std::string &game);

    private:
        void    parseLine(const std::string &line, const std::string &game);
        void    sortScores();
    };

}


#endif //CPP_ARCADE_SCORE_H
