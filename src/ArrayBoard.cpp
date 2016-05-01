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

#ifndef _NO_VALIDATIONS_
    if ((x > this->Width()) ||
        (y > this->Height()))
        throw "Out of Range";
#endif

    auto& cell = this->_board[this->_left + x][this->_top + y];

    (x == 0) && (this->_left--);
    (y == 0) && (this->_top--);
    (this->_right  - 1 >= this->_left + x) && (this->_right++);
    (this->_bottom - 1 >= this->_top  + y) && (this->_bottom++);
    // or this->_left = x - 1;

    return cell;
}

const Cell& ArrayBoard::Get(Cord x, Cord y) const {
#ifndef _NO_VALIDATIONS_
    if ((x > this->Width()) ||
        (y > this->Height()))
        return EmptyCell;
#endif

    return this->_board[this->_left + x][this->_top + y];
}

Cord ArrayBoard::Width() const {
    return this->_right - this->_left;
}

Cord ArrayBoard::Height() const {
    return this->_bottom - this->_top;
}
