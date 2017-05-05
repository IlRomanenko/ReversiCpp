//
// Created by ilya on 04.05.17.
//

#ifndef REVERSICPP_REMOTESERVER_H
#define REVERSICPP_REMOTESERVER_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace boost::asio;

using std::string;
using std::pair;

enum class GameStatus {
    WIN, LOSE, DRAW, TURN, MOVE
};

class GameTurn {

    std::pair<int, int> turn;

    GameStatus status;

public:

    GameTurn() {}

    GameTurn(int x, int y) {
        status = GameStatus::MOVE;
        turn = std::make_pair(x, y);
    }

    GameTurn(GameStatus status) {
        this->status = status;
    }

    GameStatus getStatus() const {
        return status;
    }

    pair<int, int> getTurn() const {
        return turn;
    }
};

class RemoteServer {
    ip::tcp::iostream stream;


    int readInteger() {
        int res = 0;
        unsigned char chr;
        for (int i = 0; i < 4; i++) {
            chr = (unsigned char)stream.get();
            res = (res << 8) + chr;
        }
        return res;
    }

    string readString() {
        int length = readInteger();
        char chr;
        string s;
        for (int i = 0; i < length; i++) {
            chr = (unsigned char)stream.get();
            s += chr;
        }
        return s;
    }

    void writeInteger(int value) {
        char chr[4];
        for (int i = 0; i < 4; i++) {
            chr[3 - i] = (char) (value % 256);
            value >>= 8;
        }
        for (int i = 0; i < 4; i++) {
            stream << chr[i];
        }
    }

    void writeString(string s) {
        std::cout << s << std::endl;

        writeInteger((int) s.length());
        stream << s;
    }

    int parseInt(string s) {
        int res = 0;
        for (char chr : s) {
            assert(chr >= '0' && chr <= '9');
            res = res * 10 + (chr - '0');
        }
        return res;
    }

public:
    RemoteServer(const char *hostname, const char *port, const char *token, const char *id)
            : stream(hostname, port) {
        writeString(token);
        writeString(id);
    }

    string readInit() {
        std::vector<string> v;
        string s = readString();
        s += ' ';
        string curString = "";
        for (char chr : s) {
            if (chr != ' ') {
                curString += chr;
            } else {
                v.push_back(curString);
                curString = "";
            }
        }

        if (v.size() == 2 && v[0] == "init") {
            if (v[1] == "white" || v[1] == "black") {
                return v[1];
            }  else {
                assert(false);
            }
        } else {
            assert(false);
        }

        return readString();
    }

    GameTurn readTurn() {
        string s = readString();
        std::vector<string> v;
        s += ' ';
        string curString = "";
        for (char chr : s) {
            if (chr != ' ') {
                curString += chr;
            } else {
                v.push_back(curString);
                curString = "";
            }
        }

        if (v.size() == 1) {
            string option = v.front();

            if (option == "win") {
                return GameStatus::WIN;
            } else if (option == "draw") {
                return GameStatus::DRAW;
            } else if (option == "lose") {
                return GameStatus::LOSE;
            } else if (option == "turn") {
                return GameStatus::TURN;
            } else {
                assert(false);
            }
        }

        assert(v.size() == 3 && v[0] == "move" && v[1].length() == 1);
        assert(v[2] >= "a" && v[2] <= "h");

        return {parseInt(v[1]), v[2][0] - 'a'};
    }

    void sendTurn(std::pair<int, int> turn) {
        string s = "move ";
        s += std::to_string(turn.first) + " ";
        s += turn.second + 'a';
        writeString(s);
    }
};


#endif //REVERSICPP_REMOTESERVER_H
