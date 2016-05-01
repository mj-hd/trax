#ifndef _IBOARD_H_
#define _IBOARD_H_

#include <iostream>
#include <iterator>

#include "Structs.h"

class IBoard {
public:
    ~IBoard() {};

    virtual Cell&  operator()(Cord x, Cord y) = 0;
    virtual const Cell&  Get(Cord x, Cord y) const = 0;
    virtual Cord   Width()  const = 0;
    virtual Cord   Height() const = 0;

    friend IBoard* operator<<(IBoard* b, const Operation& op);

    friend std::ostream& operator<<(std::ostream& stream, const IBoard& b);
};

#endif
