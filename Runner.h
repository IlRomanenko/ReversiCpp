//
// Created by ilya on 04.05.17.
//

#ifndef REVERSICPP_RUNNER_H
#define REVERSICPP_RUNNER_H


#include "package/IReversi.h"
#include "package/Reversi.h"
#include "RemoteServer.h"

class Runner {

    IReversi *strategy;

    RemoteServer server;

public:

    Runner(const char *host, const char *port, const char *token, const char *id)
            : server(host, port, token, id) {
        strategy = new Reversi();
    }

    void run() {
        GameTurn turn;
        while ((turn = server.readTurn()).getStatus() == GameStatus::TURN) {
            auto strategyTurn = strategy->move(turn.getTurn());
            server.sendTurn(strategyTurn);
        }
    }

    ~Runner() {
        delete strategy;
    }
};


#endif //REVERSICPP_RUNNER_H
