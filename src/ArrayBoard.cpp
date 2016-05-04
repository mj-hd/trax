#include "ArrayBoard.h"

#include <cstring>

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
        throw "Out of Range";

    auto& cell = this->_board[this->_left + x][this->_top + y];

    if (this->_right  == this->_left + x) this->_right++;
    if (this->_bottom == this->_top  + y) this->_bottom++;
    if (x == 0) this->_left--;
    if (y == 0) this->_top--;

    return cell;
}

const Cell& ArrayBoard::Get(Coord x, Coord y) const {
    if ((x >= this->Width()) ||
        (y >= this->Height()))
        return EmptyCell;

    return this->_board[this->_left + x][this->_top + y];
}

Coord ArrayBoard::Width() const {
    return this->_right - this->_left + 1;
}

Coord ArrayBoard::Height() const {
    return this->_bottom - this->_top + 1;
}

void ArrayBoard::BeginChange() {
    // TODO: implement here
}

void ArrayBoard::EndChange() {
    // TODO: implement here
}
