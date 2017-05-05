//
// Created by ilya on 04.05.17.
//

#ifndef REVERSICPP_REVERSI_H
#define REVERSICPP_REVERSI_H

#include "IReversi.h"
#include "../World.h"

class Reversi : public IReversi {

    array<array<int, 8>, 8> map;
    const int currentPlayer;

    const int turnOffsets[8][2] = {
            {-1, 0},
            {-1, 1},
            {0,  1},
            {1,  1},
            {1,  0},
            {1,  -1},
            {-1, 0},
            {-1, -1}
    };

    int getFlipLength(int x, int y, int turnIndex) {
        const auto &curOffsets = turnOffsets[turnIndex];

        int anotherPlayer = currentPlayer ^ 1;
        int flipLength = 0;

        for (int c = 1; c < 8; c++) {
            int tx = x + c * curOffsets[0], ty = y + c * curOffsets[1];
            if (tx >= 0 && tx < 8 && ty >= 0 && ty < 8) {

                if (map[tx][ty] == 0) {
                    break;
                } else if (map[tx][ty] == currentPlayer) {
                    flipLength = c - 1;
                    break;
                }
            } else {
                break;
            }
        }
        return flipLength;
    }

    bool isValidTurn(int x, int y) {
        if (map[x][y] != 0) {
            return false;
        }
        for (int i = 0; i < 8; i++) {
            if (getFlipLength(x, y, i) > 0) {
                return true;
            }
        }
        return false;
    }


public:
    Reversi(int player) : currentPlayer(player) {

    }

    pair<int, int> move(const World &world) override {
        map = world.getMap();

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (isValidTurn(i, j)) {
                    return {i, j};
                }
            }
        }

        return {0, 0};
    }

    ~Reversi() {}
};


#endif //REVERSICPP_REVERSI_H
