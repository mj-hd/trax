#ifndef _IBOARD_H_
#define _IBOARD_H_

#include <iostream>
#include <iterator>

#include "Structs.h"

class IBoard {
public:
    ~IBoard() {};

    virtual Cell&  operator()(Coord x, Coord y) = 0;
    virtual const Cell&  Get(Coord x, Coord y) const = 0;
    virtual void Set(Coord x, Coord y, Cell& cell) = 0;
    virtual Coord Width()  const = 0;
    virtual Coord Height() const = 0;

    virtual void BeginChange() = 0;
    virtual void EndChange() = 0;

    friend IBoard* operator<<(IBoard* b, const Operation& op);

    friend std::ostream& operator<<(std::ostream& stream, const IBoard& b);
};

#endif
