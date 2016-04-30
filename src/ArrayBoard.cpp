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
    auto& cell = this->_board[this->_left + x][this->_top + y];

    (this->_left   + 1 <= x) && (this->_left--);
    (this->_top    + 1 <= y) && (this->_top--);
    (this->_right  - 1 >= x) && (this->_right++);
    (this->_bottom - 1 >= y) && (this->_bottom++);
    // or this->_left = x - 1;

    return cell;
}
