#include "Host.h"

#include <iostream>

#include "ArrayBoard.h"

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

    for (auto player : this->_players) {
        operation = player->Turn();

        // TODO: do something
        // if game is over, return false
        this->_board << operation;

        std::cout << *this->_board;
    }

    return true;
}
