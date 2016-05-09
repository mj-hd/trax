#include "Player.h"

#include <iostream>
#include <string>
#include <cstdlib>

#include "Structs.h"
#include "ArrayBoard.h"
#include "IBoard.h"
#include "Exceptions.h"

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
