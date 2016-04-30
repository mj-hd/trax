#ifndef _IPLAYER_H_
#define _IPLAYER_H_

#include "IBoard.h"

class IPlayer {
public:
    virtual Operation Turn() = 0;
};

#endif
