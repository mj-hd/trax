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
dc:
        operation = player->Turn();

        // TODO: do something
        // if game is over, return false
        try {
            this->_board->BeginChange();

            this->_board << operation;

            this->_chainAround(operation.X, operation.Y);

            this->_board->EndChange();
        }
        catch (const char* message) {
            std::cerr << message << std::endl;
            goto dc;
        }

        std::cout << *this->_board;
    }

    return true;
}

void Host::_chainAround(Coord x, Coord y) {
    if (y > 0                        ) this->_chain(x,     y - 1);
    if (x < this->_board->Width() - 1) this->_chain(x + 1, y);
    if (y < this->_board->Height()- 1) this->_chain(x,     y + 1);
    if (x > 0                        ) this->_chain(x - 1, y);
}

void Host::_chain(Coord x, Coord y) {

    auto& cell = (*this->_board)(x, y);

    if (cell.Exists) return;

    char tile    = 0;
    char colored = 0;
    int  cntRed  = 0;
    int  cntWht  = 0;

    // scan neighbors
    for (auto i = 0; i < 4; i++) {
        auto sx = x + ((i*2 + 1) % 3) - 1;
        auto sy = y + ((i*2 + 1) / 3) - 1;

        auto& neighbor = this->_board->Get(sx, sy);

        if (!neighbor.Exists) continue;

        char color = ((neighbor.Color >> i) & 1);

        cntRed += color;
        cntWht += !color;

        tile    |= color << (3 - i);
        colored |= 1 << (3 - i);
    }

    if (cntRed + cntWht < 2) return;
    if (cntRed == cntWht)    return;

    cell.Color     = tile;
    cell.IsColored = colored;

    if (cntRed < cntWht) {
        for (auto i = 0; i < 4; i++) {
            if (!(colored & (1 << i)))
                cell.Color |= 1 << i;
        }
    }

    this->_chainAround(x, y);
}
