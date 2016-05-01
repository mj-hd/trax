#include "IBoard.h"

#include <sstream>

IBoard* operator<<(IBoard* b, const Operation& op) {
    (*b)(op.X, op.Y) = op.Cell;
    return b;
}

std::ostream& operator<<(std::ostream& stream, const IBoard& b) {

    auto width  = b.Width();
    auto height = b.Height();

    std::stringstream line;

    line << "  ";
    for (Cord x = 0; x < width; x++) {
        line << (char)(x + '@') << " ";
    }

    std::cout << line.str() << std::endl;

    for (Cord y = 0; y < height; y++) {

        line.str("");
        line.clear();

        line << (char)(y + '0') << " ";

        for (Cord x = 0; x < width; x++) {
            line << b.Get(x, y) << " ";
        }

        std::cout << line.str() << std::endl;
    }

    return stream;
}
