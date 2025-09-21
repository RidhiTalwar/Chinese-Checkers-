#ifndef MOVE_H
#define MOVE_H
#include "board.h"
#include <stdbool.h>

typedef struct {
    HexPos from;
    HexPos to;
} Move;

bool isValidMove(Board board, Move move, char currentPlayer);
bool canReachWithJumps(Board board, HexPos from, HexPos to, char currentPlayer, bool visited[MAX_CELLS]);
void makeMove(Board* boardPointer, Move move, char currentPlayer) ;

#endif