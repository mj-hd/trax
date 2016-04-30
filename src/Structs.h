#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <cstdint>

typedef uint_fast8_t Cord;

enum class TileType : char {
    None      = 0,
    Cross     = '+',
    Slash     = '/',
    BackSlash = '\\'
};

typedef struct {
    TileType  Type;
    std::uint_fast8_t   Direction;
}__attribute__((__packed__)) Cell;


typedef struct _Operation {
    Cord X;
    Cord Y;
    Cell Cell;

    void ToString(char& out);
    static _Operation ToOperation(const char* notation);
} Operation;

#endif
