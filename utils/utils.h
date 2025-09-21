#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include "../model/board.h"  // for Position

#define MAX_NEIGHBORS 6

bool isValidPosition(HexPos p);
void getNeighbors(HexPos p, HexPos neighbors[MAX_NEIGHBORS]);
bool isNeighbor(HexPos p, HexPos _p);
bool hasWon(Board board, char currentPlayer);

#endif