#ifndef _HOST_H_
#define _HOST_H_

#include "IBoard.h"
#include "IPlayer.h"

class Host {
public:
    Host(IPlayer* player1, IPlayer* player2);
    ~Host();
    bool Turn();

protected:
    IBoard* _board;
    IPlayer* _players[2];

    void _chain(Coord x, Coord y);
};

#endif
