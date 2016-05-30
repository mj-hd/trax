#include "ArrayBoard.h"

#include <cstring>

#include "../Structs/Exceptions.h"

ArrayBoard::ArrayBoard() {
    this->_left   = 256;
    this->_top    = 256;
    this->_right  = 256;
    this->_bottom = 256;

    std::memset(this->_board, 0, sizeof(Cell) * 512 * 512);
}

Cell& ArrayBoard::operator()(Coord x, Coord y) {
    if ((x >= this->Width()) ||
        (y >= this->Height()))
        throw new CellOutOfRangeException(x, y);

    return this->_board[this->_left + x][this->_top + y];
}

const Cell& ArrayBoard::Get(Coord x, Coord y) const {
    if ((x >= this->Width()) ||
        (y >= this->Height()))
        return EmptyCell;

    return this->_board[this->_left + x][this->_top + y];
}

void ArrayBoard::Set(Coord x, Coord y, Cell& cell) {
    this->_board[this->_left + x][this->_top + y] = cell;

    if (this->_right  == this->_left + x) this->_right  = this->_right  + 1;
    if (this->_bottom == this->_top  + y) this->_bottom = this->_bottom + 1;
    if (this->_left + x == this->_left) this->_left = this->_left - 1;
    if (this->_top  + y == this->_top)  this->_top  = this->_top  - 1;
}

Coord ArrayBoard::Width() const {
    return this->_right - this->_left + 1;
}

Coord ArrayBoard::Height() const {
    return this->_bottom - this->_top + 1;
}

void ArrayBoard::BeginChange() {
    IBoard::BeginChange();
}

void ArrayBoard::EndChange() {
    IBoard::EndChange();
}

void ArrayBoard::CancelChange() {
    IBoard::CancelChange();
}
