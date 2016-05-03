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

        this->_chain(operation.X, operation.Y);

        std::cout << *this->_board;
    }

    return true;
}

void Host::_chain(Coord x, Coord y) {

    auto& cell = (*this->_board)(x, y);

    if (cell.Exists) return;

    char tile    = 0;
    char colored = 0;
    int  cnt     = 0;

    // scan neighbors
    for (auto i = 0; i < 4; i++) {
        auto sx = x + (i % 3) - 1;
        auto sy = y + (i / 3) - 1;

        auto& neighbor = this->_board->Get(sx, sy);

        if (!neighbor.Exists) continue;

        cnt++;

        tile    |= ((neighbor.Color >> (3 - i)) & 1) << i;
        colored |= 1 << i;
    }

    if (cnt < 2) return;

    cell.Color     = tile;
    cell.IsColored = colored;

    // TODO: decide other 2 colors

    std::cout << "(" << (int)x << "," << (int)y << ")'s Chained! " << cell << std::endl;

    if (y > 2)                          this->_chain(x,     y - 1);
    if (x < this->_board->Width()  - 1) this->_chain(x + 1, y);
    if (y < this->_board->Height() - 1) this->_chain(x,     y + 1);
    if (x > 2)                          this->_chain(x - 1, y);
}
