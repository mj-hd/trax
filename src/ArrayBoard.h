#ifndef _ARRAY_BOARD_H_
#define _ARRAY_BOARD_H_

#include <cstdint>

#include "IBoard.h"

typedef std::uint_fast16_t InternalCord;

class ArrayBoard : public IBoard {
public:
    ArrayBoard();
    ~ArrayBoard() {};

    Cell& operator()(Cord x, Cord y);
    const Cell& Get(Cord x, Cord y) const;
    Cord  Width()  const;
    Cord  Height() const;

private:
    Cell _board[512][512];
    InternalCord _left;
    InternalCord _top;
    InternalCord _right;
    InternalCord _bottom;
};

#endif
