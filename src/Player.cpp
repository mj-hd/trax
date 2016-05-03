#include "Player.h"

#include <iostream>
#include <string>

#include "Structs.h"
#include "ArrayBoard.h"
#include "IBoard.h"

Player::Player() {
    this->_board = new ArrayBoard();
    //this->_board = new MapBoard();
    //this->_board = new TreeBoard();
}

Player::~Player() {
    delete this->_board;
}

Operation Player::Turn() {
    std::cout << "--- Your Turn ---" << std::endl;

input:
    std::cout << "Input Notation: ";

    std::string notation;
    std::cin >> notation;

    Operation operation;

#ifndef _NO_VALIDATIONS_
    try {
#endif

    operation = Operation::ToOperation(notation.c_str());

    //this->_board << operation;

#ifndef _NO_VALIDATIONS_
    }
    catch (const char* message) {
        std::cerr << message << std::endl;

        goto input;
    }
#endif

    return operation;
}
