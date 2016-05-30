#ifndef _IBOARD_H_
#define _IBOARD_H_

#include <iostream>
#include <iterator>
#include <vector>

#include "../Structs/Structs.h"

class IBoard {
public:
    ~IBoard() {};

    virtual Cell&  operator()(Coord x, Coord y) = 0;
    virtual const Cell&  Get(Coord x, Coord y) const = 0;
    virtual void Set(Coord x, Coord y, Cell& cell) = 0;
    virtual Coord Width()  const = 0;
    virtual Coord Height() const = 0;

    virtual void BeginChange();
    virtual void EndChange();

    virtual void CancelChange();

    friend IBoard& operator<<(IBoard& b, const Operation& op);

    friend std::ostream& operator<<(std::ostream& stream, const IBoard& b);

protected:
    virtual void _Chain(Coord x, Coord y);
    virtual void _ChainAround(Coord x, Coord y);
    virtual void _TraceLines();
    virtual int _TraceLine(Coord x, Coord y, Colors color, Direction direction, Direction* lastDirection);
    virtual void _TraceLoops(Coord x, Coord y);
    virtual bool _TraceLoop(Coord x, Coord y, Colors color, Direction direction, Coord ortX, Coord ortY);

    std::vector<Operation> _Changes;
};

#endif
