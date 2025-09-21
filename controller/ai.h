#ifndef AI_H
#define AI_H
#include "board.h"
#include "move.h"
#include "utils.h"

#define MAX_MOVES 610 //One piece can have 61 possible moves (because that many empty positions); One player has 10 pieces hence 610 possible moves.
//Note: Not all of these moves will be valid but that can be checked.

int allPossibleMoves(Board board, Move* allMoves, char currentPlayer);
int evaluateBoard(Board board, char maximizingPlayer);
int minimax(Board board, int depth, bool isMaximizing, char aiChar);
Move returnBestMove(Board board, Move* allMoves, char currentPlayer, int depth);

#endif