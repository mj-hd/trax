#include "IBoard.h"

#include <iostream>
#include <sstream>

IBoard* operator<<(IBoard* b, const Operation& op) {
    auto& cell = (*b)(op.X, op.Y);

    auto& top    = (op.Y == 0) ? EmptyCell : b->Get(op.X,     op.Y - 1);
    auto& right  =                           b->Get(op.X + 1, op.Y);
    auto& bottom =                           b->Get(op.X,     op.Y + 1);
    auto& left   = (op.X == 0) ? EmptyCell : b->Get(op.X - 1, op.Y);

    if (cell.Exists)
        throw "Cell Already Exists";

    switch (op.Type) {
        case NotationType::Cross:

            cell.Tile = TileType::Horizontal;

            // if bottom of top cell is white, do nothing
            // if bottom of top cell is red,   rotate tile
            if (top.Exists)    { cell.Type <<= top.Bottom;  break; }
            if (right.Exists)  { cell.Type <<= !right.Left; break; }
            if (bottom.Exists) { cell.Type <<= bottom.Top;  break; }
            if (left.Exists)   { cell.Type <<= !left.Right; break; }

            break;
        case NotationType::Slash:

            cell.Tile = TileType::None;

            // copy neighbors color
            if (top.Exists) {
                cell.Top           = top.Bottom;
                cell.Left          = top.Bottom;
                cell.ColoredTop    = 1;
                cell.ColoredLeft   = 1;
            }
            if (right.Exists)  {
                cell.Right         = right.Left;
                cell.Bottom        = right.Left;
                cell.ColoredRight  = 1;
                cell.ColoredBottom = 1;
            }
            if (bottom.Exists) {
                cell.Bottom        = bottom.Top;
                cell.Right         = bottom.Top;
                cell.ColoredBottom = 1;
                cell.ColoredRight  = 1;
            }
            if (left.Exists)   {
                cell.Left          = left.Right;
                cell.Top           = left.Right;
                cell.ColoredLeft   = 1;
                cell.ColoredTop    = 1;
            }

            goto decideOtherColors;

        case NotationType::BackSlash:

            cell.Tile = TileType::None;

            // copy neighbors color
            if (top.Exists) {
                cell.Top           = top.Bottom;
                cell.Right         = top.Bottom;
                cell.ColoredTop    = 1;
                cell.ColoredRight  = 1;
            }
            if (right.Exists)  {
                cell.Right         = right.Left;
                cell.Top           = right.Left;
                cell.ColoredRight  = 1;
                cell.ColoredTop    = 1;
            }
            if (bottom.Exists) {
                cell.Bottom        = bottom.Top;
                cell.Left          = bottom.Top;
                cell.ColoredBottom = 1;
                cell.ColoredLeft   = 1;
            }
            if (left.Exists)   {
                cell.Left          = left.Right;
                cell.Bottom        = left.Right;
                cell.ColoredLeft   = 1;
                cell.ColoredBottom = 1;
            }

decideOtherColors:
            // decide other 2 colors
            if (!cell.ColoredTop)    { cell.Top    = !cell.Bottom; }
            if (!cell.ColoredRight)  { cell.Right  = !cell.Left; }
            if (!cell.ColoredBottom) { cell.Bottom = !cell.Top; }
            if (!cell.ColoredLeft)   { cell.Left   = !cell.Right; }

            /*
             * TODO: compare performance
            for (auto i = 0; i < 4; i++) {
                if (!(cell.IsColored & (1 << i)))
                    if (!((cell.Color >> (3 - i)) & 1))
                        cell.Color |= 1 << i;
            }*/


            break;
    }

    return b;
}

std::ostream& operator<<(std::ostream& stream, const IBoard& b) {

    auto width  = b.Width();
    auto height = b.Height();

    std::stringstream line;

    line << std::endl << "  ";
    for (Coord x = 0; x < width; x++) {
        line << (char)(x + '@') << " ";
    }

    std::cout << line.str() << std::endl;

    for (Coord y = 0; y < height; y++) {

        line.str("");
        line.clear();

        line << (char)(y + '0') << " ";

        for (Coord x = 0; x < width; x++) {
            line << b.Get(x, y) << " ";
        }

        std::cout << line.str() << std::endl;
    }

    return stream;
}
