#include "MineSweeperGame.h"

int main(){
    MineSweeperGame* game = new MineSweeperGame();
    game->initialize();
    return game->run();
}