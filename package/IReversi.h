//
// Created by ilya on 04.05.17.
//
#pragma once

#ifndef REVERSICPP_IREVERSI_H
#define REVERSICPP_IREVERSI_H

#include <utility>
#include <vector>
#include "../World.h"

using std::pair;
using std::vector;

class IReversi {
public:
    IReversi() { }
    virtual pair<int, int> move(const World& world) = 0;
    virtual ~IReversi() { }
};

#endif //REVERSICPP_IREVERSI_H
