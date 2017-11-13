//
// Created by dommer_c on 17/04/17.
//

#include "Scoring.h"

bool comparePair(std::pair<std::string, int> a, std::pair<std::string, int> b) {
    return (a.second > b.second);
}

void arcade::Scoring::saveScore(const std::string &game, const std::string &playerName, const int &score) {
    std::ofstream   myFile;

    myFile.open("scores.txt", std::ios::app);
    myFile << game << "-" << playerName << "-" << std::to_string(score) << std::endl;
    myFile.close();
}

std::vector<std::pair<std::string, int>> &arcade::Scoring::getScores(const std::string &game) {
    std::ifstream       myFile;
    std::string         line;

    myFile.open("scores.txt");
    this->_scores.clear();
    while (getline(myFile, line)) {
        this->parseLine(line, game);
    }
    myFile.close();
    this->sortScores();
    return this->_scores;
}

void arcade::Scoring::parseLine(const std::string &line, const std::string &game) {
    std::size_t     first;
    std::size_t     second;
    std::string     name;
    std::string     score;

    first = line.find("-");
    if (line.compare(0, first, game) == 0) {
        second = line.find("-", first + 1);
        name = line.substr(first + 1, second - first - 1);
        score = line.substr(second + 1);
        this->_scores.push_back(std::make_pair(name, std::stoi(score, nullptr, 10)));
    }
}

void arcade::Scoring::sortScores() {
    std::vector<std::pair<std::string, int>>::iterator  begin = this->_scores.begin();
    std::vector<std::pair<std::string, int>>::iterator  end = this->_scores.end();
    std::sort(begin, end, comparePair);
}
