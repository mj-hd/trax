#include "IBoard.h"

#include <iostream>
#include <sstream>

#include "Exceptions.h"

IBoard* operator<<(IBoard* b, const Operation& op) {

    auto cell = b->Get(op.X, op.Y);

    auto& top    = (op.Y == 0) ? EmptyCell : b->Get(op.X,     op.Y - 1);
    auto& right  =                           b->Get(op.X + 1, op.Y);
    auto& bottom =                           b->Get(op.X,     op.Y + 1);
    auto& left   = (op.X == 0) ? EmptyCell : b->Get(op.X - 1, op.Y);

    // validations
    // tile already exists
    if (cell.Exists)
        throw new TileAlreadyExistsException(op.X, op.Y);

    // not allowed for first operation
    if (b->Width() == 1 && b->Height() == 1) {
        if (op.X != 0 || op.Y != 0 || op.Type != NotationType::Cross)
            throw new InvalidPlacementException(op.X, op.Y); // TODO: InvalidFirstOperationException
    } else {
        if (!top.Exists && !right.Exists && !bottom.Exists && !left.Exists)
            throw new InvalidPlacementException(op.X, op.Y); // TODO: IsolatedPlacementException
    }

    // 3 same colors
    if ((top.Exists ? 1 : 0) + (right.Exists ? 1 : 0) +
        (bottom.Exists ? 1 : 0) + (left.Exists ? 1 : 0) >= 3) {
        int cnt = top.Bottom + right.Left + bottom.Top + left.Right;
        if (cnt == 0 || cnt >= 3) throw new InvalidPlacementException(op.X, op.Y);
    }

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

    b->Set(op.X, op.Y, cell);

    b->_Changes.push_back(op);

    b->_ChainAround(op.X, op.Y);

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

void IBoard::BeginChange() {
    this->_Changes.clear();
}

void IBoard::EndChange() {
    for (const auto& change : this->_Changes) {
        // TODO: tile should be placed here

    }

    this->_TraceLines();

    if (this->_DetectCheckmate())
        throw new GameOverException(Colors::Red); // TODO: set correct winner
}

void IBoard::CancelChange() {
    for (auto change = this->_Changes.end(); change != this->_Changes.begin(); change--) {
        // TODO: implement here
    }
}

void IBoard::_Chain(Coord x, Coord y) {

    auto cell = this->Get(x, y);

    if (cell.Exists) return;

    char tile    = 0;
    char colored = 0;
    int  cntRed  = 0;
    int  cntWht  = 0;

    // scan neighbors
    for (auto i = 0; i < 4; i++) {
        auto sx = x + ((i*2 + 1) % 3) - 1;
        auto sy = y + ((i*2 + 1) / 3) - 1;

        auto& neighbor = this->Get(sx, sy);

        if (!neighbor.Exists) continue;

        char color = ((neighbor.Color >> i) & 1);

        cntRed += color;
        cntWht += !color;

        tile    |= color << (3 - i);
        colored |= 1 << (3 - i);
    }

    if (cntRed + cntWht < 2) return;
    if (cntRed == cntWht)    return;

    if (cntRed > 2 || cntWht > 2) throw new ChainFailedException(x, y);

    cell.Color     = tile;
    cell.IsColored = colored;

    if (cntRed < cntWht) {
        for (auto i = 0; i < 4; i++) {
            if (!(colored & (1 << i)))
                cell.Color |= 1 << i;
        }
    }

    this->Set(x, y, cell);
    // TODO: generate chain notation
    //this->_Changes.push_back(Operation {x, y, (NotationType)cell.Type});

    this->_ChainAround(x, y);

}

void IBoard::_ChainAround(Coord x, Coord y) {
    if (y > 0                ) this->_Chain(x,     y - 1);
    if (x < this->Width() - 1) this->_Chain(x + 1, y);
    if (y < this->Height()- 1) this->_Chain(x,     y + 1);
    if (x > 0                ) this->_Chain(x - 1, y);
}

void IBoard::_TraceLines() {
    Direction lastDirection;
    Colors    color;

    // vertical
    for (Coord y = 1; y < this->Height() - 1; y++) {

        color = this->Get(1, y).Color & (unsigned char)Direction::Left ? Colors::Red : Colors::White;

        if (this->_TraceLine(1, y, color, Direction::Left, &lastDirection) >= 8)
            if (lastDirection == Direction::Right)
                throw new GameOverException(color); // TODO: WiningLineException
    }

    // horizontal
    for (Coord x = 1; x < this->Width() - 1; x++) {

        color = this->Get(x, 1).Color & (unsigned char)Direction::Left ? Colors::Red : Colors::White;

        if (this->_TraceLine(x, 1, color, Direction::Top, &lastDirection) >= 8)
            if (lastDirection == Direction::Bottom)
                throw new GameOverException(color); // TODO: WiningLineException

    }
}

int IBoard::_TraceLine(Coord x, Coord y, Colors color, Direction direction, Direction* lastDirection) {
    auto cell = this->Get(x, y);

    if (!cell.Exists) return 0;

    if (color == Colors::White) cell.Color = ~cell.Color;

    auto directions = cell.Color & (unsigned char)Colors::Red;

    for (auto i = 0; i < 4; i++) {
        if ((directions >> (3 - i)) & 1) {
            if (((unsigned char)direction >> (3 - i)) & 1) continue;

            auto sx = (i * 2 + 1) % 3 - 1;
            auto sy = (i * 2 + 1) / 3 - 1;

            *lastDirection = (Direction)(1 << (3 - i));

            return 1 + this->_TraceLine(x + sx, y + sy, color, (Direction)(1 << i), lastDirection);
        }
    }

    return 1;
}

bool IBoard::_DetectCheckmate() {
    // TODO: implement here
    return false;
}
