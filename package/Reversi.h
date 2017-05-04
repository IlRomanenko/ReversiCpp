//
// Created by ilya on 04.05.17.
//

#ifndef REVERSICPP_REVERSI_H
#define REVERSICPP_REVERSI_H

#include "IReversi.h"

class Reversi : public IReversi{

public:
    Reversi() { }

    std::pair<char, int> move(std::pair<char, int> opponentMove) override {
        return {'a', 1};
    }

    ~Reversi() { }
};


#endif //REVERSICPP_REVERSI_H
