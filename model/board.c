#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void initializeBoard(Board* board) {
    /*
    - This function loops from y = -8 to y = -5 and inside the cells 0-9 in the cells array, it initializes the player as 'R'.
    - It then loops through y = -4 to y = +4 and inside the cells 10-70 in the cells array, it initializes the player as '.'.
    - It then loops through y = +5 to y = +8 and inside the cells 71-80 in the cells array, it initializes the player as 'B'.
    */
    int i = 0; 
    for(int y = -8; y <= -5; y++) {
        int range = 8 - abs(y);
        for(int x = 4 - range; x <= 4; x++) {
            board->cells[i].pos.x = x;
            board->cells[i].pos.y = y;
            board->cells[i].player = 'R';
            i++;
        }
    }
    for(int y = -4; y <= 0; y++) {
        int range = 8 - abs(y);
        for(int x = 4 - range; x <= 4; x++) {
            board->cells[i].pos.x = x;
            board->cells[i].pos.y = y;
            board->cells[i].player = '.';
            i++;
        }
    }
    for(int y = 1; y <= 4; y++) {
        int range = 8 - abs(y);
        for(int x = -4; x <= -4 + range; x++) {
            board->cells[i].pos.x = x;
            board->cells[i].pos.y = y;
            board->cells[i].player = '.';
            i++;
        }
    }
    for(int y = 5; y <= 8; y++) {
        int range = 8 - abs(y);
        for(int x = -4; x <= -4 + range; x++) {
            board->cells[i].pos.x = x;
            board->cells[i].pos.y = y;
            board->cells[i].player = 'B';
            i++;
        }
    }
}

int getCellIndex(Board board, HexPos p) {
    /*
    For each position on the board, it allows us to access the index at which the cell with that position is stored inside the cell array.
    Then we can access which player resides at that cell at that point as well.
    This function is basically connects the cell position to the player that's standing on it via the cell array.
    */
    for (int i = 0; i < MAX_CELLS; i++) {
        if (board.cells[i].pos.x == p.x && board.cells[i].pos.y == p.y) {
            return i;
        }
    }
    return -1; // If no such position exists, the cell index is returned as -1. Standard convention for invalid index.
}