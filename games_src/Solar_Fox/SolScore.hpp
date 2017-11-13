//
// Created by pierre on 14/03/17.
//

#ifndef CPP_ARCADE_SCORE_HPP
#define CPP_ARCADE_SCORE_HPP

namespace arcade {
    class SolScore
    {
    private:
        int     _score;

    public:
        SolScore();
        virtual ~SolScore();
        int get_score() const;
        void set_score(int _score);
        void operator+=(int a);
    };
}

#endif //CPP_ARCADE_SCORE_HPP
