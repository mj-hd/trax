#include "Player/IPlayer.h"
#include "Player/Player.h"
#include "Host.h"
//#include "Bot.h"

#include "Structs/Exceptions.h"

int main(int argc, char* argv[]) {

    auto player1 = new Player();
    auto player2 = new Player();
    //auto player2 = new Bot();

    auto host = new Host(player1, player2);

    try {
        while(host->Turn());
    }
    catch (Exception* e) {
        std::cerr << e->GetMessage() << std::endl;

        goto end;
    }

end:
    delete host;
    delete player1, player2;
}
