#ifndef _ARRAY_BOARD_H_
#define _ARRAY_BOARD_H_

#include <cstdint>

#include "IBoard.h"

typedef std::uint_fast16_t InternalCoord;

class ArrayBoard : public IBoard {
public:
    ArrayBoard();
    ~ArrayBoard() {};

    Cell& operator()(Coord x, Coord y);
    const Cell& Get(Coord x, Coord y) const;
    Coord Width()  const;
    Coord Height() const;

    void BeginChange();
    void EndChange();

private:
    Cell _board[512][512];
    InternalCoord _left;
    InternalCoord _top;
    InternalCoord _right;
    InternalCoord _bottom;
};

#endif
