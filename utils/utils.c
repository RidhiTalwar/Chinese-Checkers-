#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "board.h"

bool isValidPosition(HexPos p) {
    /*
    - Checks coordinate arithmetic to check if the position exists and is valid or not.
    - An equally-accurate alternate implementation of this function could've been to check if getCellIndex() == -1
      However, this is marginally faster as this doesn't involve array traversal.
    */
    int range = 8 - abs(p.y);
    if (p.y <= 0 && p.y >= -8) {
        return (p.x >= (4 - range) && p.x <= 4);
    } else if (p.y > 0 && p.y <= 8) {
        return (p.x >= -4 && p.x <= (-4 + range));
    }
    return false;
}

void getNeighbors(HexPos p, HexPos neighbors[MAX_NEIGHBORS]) {
    /*
    Initializes an array with all the valid neighbours of a given position
    */
    int i = 0;
    HexPos possibleNeighbors[MAX_NEIGHBORS]; //Stores all possible neighbours of p, even those that might be invalid
    possibleNeighbors[i++] = (HexPos){p.x + 1, p.y}; //East
    possibleNeighbors[i++] = (HexPos){p.x - 1, p.y}; //West
    possibleNeighbors[i++] = (HexPos){p.x, p.y + 1}; //South-East
    possibleNeighbors[i++] = (HexPos){p.x, p.y - 1}; //North-West
    possibleNeighbors[i++] = (HexPos){p.x - 1, p.y + 1}; //South-West
    possibleNeighbors[i++] = (HexPos){p.x + 1, p.y - 1}; //North-East
    int count = 0;
    for(int j = 0; j < MAX_NEIGHBORS; j++) {
        if (isValidPosition(possibleNeighbors[j])) { //Only adds the valid ones out of possibleNeighbors to neighbors
            neighbors[count++] = possibleNeighbors[j];
        }
    }
    while(count != MAX_NEIGHBORS) {
        neighbors[count++] = INVALID_POSITION(); //Fills the remaining space in neighbors with INVALID_POSITION() i.e. (HexPos){99, 99}
    }
}

bool isNeighbor(HexPos p, HexPos _p) {
    /*
    Checks if a _p is a neighbour of p
    */
    HexPos neighbors[MAX_NEIGHBORS];
    getNeighbors(p, neighbors);
    //Loops through all the neighbours of p to check if one of them matches _p
    for(int i = 0; i < MAX_NEIGHBORS; i++) {
        if (neighbors[i].x == (_p).x && neighbors[i].y == (_p).y) {
            //We aren't checking is position is valid or not as 99 won't match _p.x or _p.y anyway.
            return true;
        }
    }
    return false;
}

bool hasWon(Board board, char currentPlayer) {
    /*
    Checks if that currentPlayer has won i.e. occupied all the 10 opposite positions:-
    - It's given the currentPlayer, all the pieces of which either occupied the top 4-row triangle our board or the bottom triangle in the beginning.
    - Now the win position would entail that all the pieces of that player fully occupy the opposite triangle.
    - For 'B', this would be the top triangle. The coordinates of the top triangle correspond to cells 0-9 in the cell array according to our initialization logic.
    - So for 'B', it would check if all cells with index 0-9 in the cell array, have 'B' as the player to check if 'B' has won.
    - Similarly, for 'R', it would check if all cells with index 71-80 in the cell array, have 'R' as the player to check if 'R' has won.
    */
    bool hasWon = true;
    if (currentPlayer == 'B') {
        for(int i = 0; i <= 9; i++) {
            if (board.cells[i].player != 'B') {
                hasWon = false;
                break;
            }
        }
    } else if (currentPlayer == 'R') {
        for(int i = 71; i <= 80; i++) {
            if (board.cells[i].player != 'R') {
                hasWon = false;
                break;
            }
        }
    }
    return hasWon;
}