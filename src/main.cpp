#include "IPlayer.h"
#include "Player.h"
#include "Host.h"
//#include "Bot.h"

int main(int argc, char* argv[]) {

    auto player1 = new Player();
    auto player2 = new Player();
    //auto player2 = new Bot();

    auto host = new Host(player1, player2);

    while(host->Turn());

    delete host;
    delete player1, player2;
}
