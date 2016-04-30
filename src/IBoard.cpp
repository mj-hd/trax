#include "IBoard.h"

IBoard* operator<<(IBoard* b, const Operation& op) {
    (*b)(op.X, op.Y) = op.Cell;
    return b;
}

std::ostream& operator<<(std::ostream& stream, const IBoard& b) {
    stream << "TODO" << std::endl;
}
