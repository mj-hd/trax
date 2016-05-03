#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <iostream>
#include <cstdint>

typedef uint_fast8_t Cord;

enum class Colors : char {
    Red   = 0b1111111,
    Black = 0b1111111,
    White = 0b0000000
};

// names indicate where red points are
enum class TileType : char {
    None        = 0b00000000,
    Horizontal  = 0b00000101,
    Vertical    = 0b00001010,
    TopRight    = 0b00001100,
    RightBottom = 0b00000110,
    BottomLeft  = 0b00000011,
    LeftTop     = 0b00001001
};

static char TileChars[16] = {
    ' ', '?', '?', 'e', '?', 'a', 'd', '?', '?', 'f', 'b', '?', 'c', '?', '?', '?'
};

union Cell {
    struct {
        char MetaData : 4;
        char Type : 4;
    };
    struct {
        char        : 4;
        char Top    : 1;
        char Right  : 1;
        char Bottom : 1;
        char Left   : 1;
    } Color;
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
    Cord X;
    Cord Y;
    NotationType Type;

    void ToString(char* out) const;
    static Operation ToOperation(const char* notation);
    friend std::ostream& operator<<(std::ostream& stream, const Operation& o);
};

#endif
