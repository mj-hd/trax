#include "Host.h"

Host::Host(IPlayer* player1, IPlayer* player2) {
    this->_players[0] = player1;
    this->_players[1] = player2;

    this->_board = new ArrayBoard();
}

Host::~Host() {
    delete this->_board;
}

bool Host::Turn() {

    Operation operation;

    for (auto player : players) {
        operation = player->Turn();

        // TODO: do something
        // if game is over, return false
    }

    return true;
}
