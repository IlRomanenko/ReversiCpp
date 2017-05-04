//
// Created by ilya on 04.05.17.
//
#pragma once

#ifndef REVERSICPP_IREVERSI_H
#define REVERSICPP_IREVERSI_H

#include <utility>

class IReversi {
public:
    IReversi() { }
    virtual std::pair<char, int> move(std::pair<char, int> opponentMove) = 0;
    virtual ~IReversi() { }
};

#endif //REVERSICPP_IREVERSI_H
