#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "IPlayer.h"

#include "ArrayBoard.h"
#include "Structs.h"

class Player : public IPlayer {
public:
    Player();
    ~Player();

    Operation Turn();

protected:
    IBoard* _board;
};

#endif
