#ifndef _IPLAYER_H_
#define _IPLAYER_H_

#include "../Board/IBoard.h"

class IPlayer {
public:
    virtual Operation Turn() = 0;
};

#endif
