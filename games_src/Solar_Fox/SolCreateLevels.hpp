//
// Created by pierre on 12/04/17.
//

#ifndef TEST_ARCADE_CREATELEVELS_HPP
#define TEST_ARCADE_CREATELEVELS_HPP


#include <vector>
#include <array>

namespace arcade
{
    class SolLevelsCreator {
    private:
        std::vector<std::pair<std::array<std::array<int, 20>, 20>, int>>  _levels;

    public:
        SolLevelsCreator(int mapWidth, int mapHeight);
        virtual ~SolLevelsCreator();
        int getValue(int x, int y, int n) const;
    };
}

#endif //TEST_ARCADE_CREATELEVELS_HPP
