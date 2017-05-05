//
// Created by ilya on 04.05.17.
//

#ifndef REVERSICPP_RUNNER_H
#define REVERSICPP_RUNNER_H


#include "package/IReversi.h"
#include "package/Reversi.h"
#include "RemoteServer.h"
#include "World.h"

class Runner {

    IReversi *strategy;

    RemoteServer server;

public:

    Runner(const char *host, const char *port, const char *token, const char *id)
            : server(host, port, token, id) {
    }

    void run() {
        GameTurn turn;
        World world(server.readInit());

        int player = 0, anotherPlayer;
        if (world.getColor() == "black") {
            player = 1;
        } else {
            player = 2;
        }
        anotherPlayer = 3 - player;

        strategy = new Reversi(player);

        vector<pair<int, int> > moves;
        while (true) {
            moves.clear();
            while ((turn = server.readTurn()).getStatus() == GameStatus::MOVE) {
                moves.push_back(turn.getTurn());
                std::cout << turn.getTurn().first << ' ' << turn.getTurn().second << endl;
            }
            if (turn.getStatus() == GameStatus::TURN) {
                world.processTurns(moves, anotherPlayer);

                auto strategyTurn = strategy->move(world);

                server.sendTurn(strategyTurn);

                world.processTurns({strategyTurn}, player);

            } else {
                break;
            }
        }
    }

    ~Runner() {
        delete strategy;
    }
};


#endif //REVERSICPP_RUNNER_H
