#include <stdio.h>
#include "player.h"

void switchPlayer(char* currentPlayer) {
    /*
    - This function is used in the main() function in the if block of the 2-player mode
    - Its purpose is to switch the current player to the other player when its time to change turns
    */
    *currentPlayer = (*currentPlayer == 'R') ? 'B' : 'R';
}