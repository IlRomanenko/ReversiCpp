//
// Created by ilya on 04.05.17.
//

#ifndef REVERSICPP_REMOTESERVER_H
#define REVERSICPP_REMOTESERVER_H

#include <ios>
#include <string>
#include <boost/asio.hpp>

using namespace boost::asio;

using std::string;

enum class GameStatus {
    WIN, LOSE, DRAW, TURN
};

class GameTurn {

    std::pair<char, int> turn;

    GameStatus status;

public:

    GameTurn() { }

    GameTurn(char x, int y) {
        status = GameStatus::TURN;
        turn = std::make_pair(x, y);
    }

    GameTurn(GameStatus status) {
        this->status = status;
    }

    GameStatus getStatus() const {
        return status;
    }

    std::pair<char, int> getTurn() const {
        return turn;
    }
};

class RemoteServer {
    ip::tcp::iostream stream;


    int readInteger() {
        int res = 0;
        unsigned char chr;
        for (int i = 0; i < 4; i++) {
            stream >> chr;
            res = (res << 8) + chr;
        }
        return res;
    }

    string readString() {
        int length = readInteger();
        char chr;
        string s;
        for (int i = 0; i < length; i++) {
            stream >> chr;
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
        stream << chr;
    }

    void writeString(string s) {
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
            if (v[0] == "WIN") {
                return GameStatus::WIN;
            } else if (v[0] == "DRAW") {
                return GameStatus::DRAW;
            } else if (v[1] == "LOSE") {
                return GameStatus::LOSE;
            } else {
                assert(false);
            }
        }

        assert(v.size() == 3 && v[0] == "move" && v[1].length() == 1);
        assert(v[1] >= "a" && v[1] <= "h");

        return {v[1][0], parseInt(v[2])};
    }

    void sendTurn(std::pair<char, int> turn) {
        string s = "move " + std::to_string(turn.first) + " " + std::to_string(turn.second);
        writeString(s);
    }
};


#endif //REVERSICPP_REMOTESERVER_H
