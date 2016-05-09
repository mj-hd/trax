#include "Host.h"

#include <iostream>

#include "ArrayBoard.h"
#include "Exceptions.h"

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

    for (auto& player : this->_players) {
dc:
        operation = player->Turn();

        try {
            this->_board->BeginChange();

            this->_board << operation;

            this->_board->EndChange();
        }
        // GameOver
        catch (GameOverException* e) {
            std::cerr << e->GetMessage() << std::endl;
            std::cerr << "Winner is " << (e->GetWinner() == Colors::Red ? "Red" : "White") << std::endl;

            return false;
        }
        catch (InvalidPlacementException* e) {
            std::cerr << e->GetMessage() << std::endl;

            this->_board->CancelChange();

            goto dc;
        }

        std::cout << *this->_board;
    }

    return true;
}
