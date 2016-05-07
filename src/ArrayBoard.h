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
    void Set(Coord x, Coord y, Cell& cell);
    Coord Width()  const;
    Coord Height() const;

    void BeginChange();
    void EndChange();
    void CancelChange();

private:
    Cell _board[512][512];
    InternalCoord _left;
    InternalCoord _top;
    InternalCoord _right;
    InternalCoord _bottom;
    InternalCoord _leftInChange;
    InternalCoord _topInChange;
    InternalCoord _rightInChange;
    InternalCoord _bottomInChange;
};

#endif
