//
// Created by ilya on 05.05.17.
//

#ifndef REVERSICPP_WORLD_H
#define REVERSICPP_WORLD_H

#include <vector>
#include <utility>
#include <array>



#include <iostream>
using namespace std;

using std::vector;
using std::pair;
using std::array;
using std::string;

class World {

    array<array<int, 8>, 8> map;
    const int turnOffsets[8][2] = {
            {-1, 0},
            {-1, 1},
            {0,  1},
            {1,  1},
            {1,  0},
            {1,  -1},
            {0, -1},
            {-1, -1}
    };

    int getFlipLength(int x, int y, int turnOffsetIndex, int player) {
        const auto& turnOffset = turnOffsets[turnOffsetIndex];
        int revertLength = 0;
        for (int c = 1; c < 8; c++) {
            int tx = x + turnOffset[0] * c, ty = y + turnOffset[1] * c;

            if (tx >= 0 && tx < 8 && ty >= 0 && ty < 8) {
                if (map[tx][ty] == 0) {
                    break;
                } else if (map[tx][ty] == player) {
                    revertLength = c - 1;
                    break;
                }
            } else {
                break;
            }
        }
        return revertLength;
    }

    void flip(int x, int y, int player) {
        map[x][y] = player;
        for (int j = 0; j < 8; j++) {

            int length = getFlipLength(x, y, j, player);
            for (int c = 1; c <= length; c++) {
                map[x + turnOffsets[j][0] * c][y + turnOffsets[j][1] * c] = player;
            }
        }
    }

    vector<pair<int, int> > latestMoves;

    string color;

public:

    World(string color) {
        this->color = color;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                map[i][j] = 0;
            }
        }
        map[3][3] = 2;
        map[3][4] = 1;
        map[4][3] = 1;
        map[4][4] = 2;
    }


    void processTurns(vector<pair<int, int> > v, int player) {
        latestMoves = v;
        for (const auto& turn : v) {
            flip(turn.first, turn.second, player);
        }
    }

    const string getColor() const {
        return color;
    }

    const vector<pair<int, int> > getLatestMoves() const {
        return latestMoves;
    }

    const array<array<int, 8>, 8> getMap() const {
        return map;
    }

    void printMap() {
        cout << endl << endl;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cout << map[i][j] << ' ';
            }
            cout << endl;
        }

        cout << endl << endl;
    }

};

#endif //REVERSICPP_WORLD_H
