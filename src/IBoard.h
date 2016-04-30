#ifndef _IBOARD_H_
#define _IBOARD_H_

#include <iostream>

#include "Structs.h"

class IBoard {
public:
    ~IBoard() {};

    virtual Cell&  operator()(Cord x, Cord y) = 0;

    friend IBoard* operator<<(IBoard* b, const Operation& op);

    friend std::ostream& operator<<(std::ostream& stream, const IBoard& b);
};

#endif
