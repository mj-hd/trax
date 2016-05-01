#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <iostream>
#include <cstdint>

typedef uint_fast8_t Cord;

enum class TileType : char {
    None      = 0,
    Cross     = '+',
    Slash     = '/',
    BackSlash = '\\'
};

typedef struct _Cell {
    TileType  Type;
    friend std::ostream& operator<<(std::ostream& stream, const _Cell& c);
}__attribute__((__packed__)) Cell;

static constexpr Cell EmptyCell = Cell { TileType::None };


typedef struct _Operation {
    Cord X;
    Cord Y;
    Cell Cell;

    void ToString(char* out) const;
    static _Operation ToOperation(const char* notation);
    friend std::ostream& operator<<(std::ostream& stream, const _Operation& o);
} Operation;

#endif
