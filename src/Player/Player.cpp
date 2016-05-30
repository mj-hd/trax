#include "Player.h"

#include <iostream>
#include <string>
#include <cstdlib>

#include "../Structs/Structs.h"
#include "../Structs/Exceptions.h"
#include "../Board/IBoard.h"
#include "../Board/ArrayBoard.h"

Player::Player()
    : _board(*new ArrayBoard()) {
}

Player::~Player() {
    delete &this->_board;
}

Operation Player::Turn() {
    std::cout << "--- Your Turn ---" << std::endl;

input:
    std::cout << "Input Notation: ";

    std::string notation;
    std::cin >> notation;

    if (std::cin.eof()) { std::exit(0); }

    Operation operation;

    try {

        operation = Operation::ToOperation(notation.c_str());

        //this->_board->BeginChange();

        //this->_board << operation;

        //this->_board->EndChange();
    }
    catch (InvalidNotationException* e) {
        std::cerr << e->GetMessage() << std::endl;

        goto input;
    }
    catch (InvalidPlacementException* e) {
        std::cerr << e->GetMessage() << std::endl;

        goto input;
    }

    return operation;
}
