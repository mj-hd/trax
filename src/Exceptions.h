#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include "Structs.h"

class Exception {
public:
    Exception(const char* message)   { this->_Message = message; };
    virtual const char* GetMessage() { return this->_Message; }

protected:
    const char* _Message;
};

class GameOverException : public Exception {
public:
    GameOverException(Colors winner)
        : Exception("Game Over") {
        this->_winner = winner;
    }

    Colors GetWinner() { return this->_winner; };

private:
    Colors _winner;
};

class InvalidPlacementException : public Exception {
public:
    InvalidPlacementException(Coord x, Coord y)
        : Exception("Invalid Placement") {
        this->_x = x;
        this->_y = y;
    }

    Coord GetX() { return this->_x; };
    Coord GetY() { return this->_y; };

private:
    Coord _x;
    Coord _y;
};

class TileAlreadyExistsException : public InvalidPlacementException {
public:
    TileAlreadyExistsException(Coord x, Coord y)
        : InvalidPlacementException(x, y) {
        this->_Message = "Tile Already Exists";
    }
};

class CellOutOfRangeException : public InvalidPlacementException {
public:
    CellOutOfRangeException(Coord x, Coord y)
        : InvalidPlacementException(x, y) {
        this->_Message = "Cell Out Of Range";
    }
};

class ChainFailedException : public InvalidPlacementException {
public:
    ChainFailedException(Coord x, Coord y)
        : InvalidPlacementException(x, y) {
        this->_Message = "Chain Failed";
    }
};

class InvalidNotationException : public Exception {
public:
    InvalidNotationException()
        : Exception("Invalid Notation") {}
};
#endif
