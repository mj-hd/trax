#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <iostream>
#include <cstdint>

typedef uint_fast8_t Coord;

enum class Colors : unsigned char {
    Red   = 0b1111111,
    Black = 0b1111111,
    White = 0b0000000
};

// names indicate where red points are
// -----------
// |    1    |
// | 2     3 |
// |    4    |
// -----------
enum class TileType : unsigned char {
    None        = 0b00000000, //   0
    Horizontal  = 0b11110110, // a 6
    Vertical    = 0b11111001, // b 9
    TopRight    = 0b11111010, // c 10
    RightBottom = 0b11110011, // d 3
    BottomLeft  = 0b11110101, // e 5
    LeftTop     = 0b11111100  // f 12
};

static char TileChars[16] = {
    ' ', '1', '2', 'd', '3', 'e', 'a', '4', '5', 'b', 'c', '6', 'f', '7', '8', '9'
};

union Cell {
    struct {
        // lsb
        unsigned char Type   : 4;
        unsigned char Exists : 4;
        // msb
    };
    struct {
        // lsb
        unsigned char Color     : 4;
        unsigned char IsColored : 4;
        // msb
    };
    struct {
        // lsb
        unsigned char Bottom : 1;
        unsigned char Right  : 1;
        unsigned char Left   : 1;
        unsigned char Top    : 1;
        unsigned char ColoredBottom  : 1;
        unsigned char ColoredRight   : 1;
        unsigned char ColoredLeft    : 1;
        unsigned char ColoredTop     : 1;
        // msb
    };
    TileType Tile;

    friend std::ostream& operator<<(std::ostream& stream, const Cell& c);
    char ToString() const;
}__attribute__((__packed__));

static constexpr Cell EmptyCell = Cell { .Tile = TileType::None };

enum class NotationType : char {
    Cross     = '+',
    Slash     = '/',
    BackSlash = '\\'
};

struct Operation {
    Coord X;
    Coord Y;
    NotationType Type;

    void ToString(char* out) const;
    static Operation ToOperation(const char* notation);
    friend std::ostream& operator<<(std::ostream& stream, const Operation& o);
};

#endif
