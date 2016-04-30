#include "ArrayBoard.h"

#include <cstring>

ArrayBoard::ArrayBoard() {
    this->_left   = 255;
    this->_top    = 255;
    this->_right  = 257;
    this->_bottom = 257;

    std::memset(this->_board, 0, sizeof(Cell) * 512 * 512);
}

Cell& ArrayBoard::operator()(Cord x, Cord y) {
    return this->_board[this->_left + x][this->_top + y];
}
