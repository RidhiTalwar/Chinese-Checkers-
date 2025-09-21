#ifndef BOARD_H
#define BOARD_H

#define MAX_CELLS 81 //20 occupied by pieces + 61 initially empty
#define MAX_PIECES 20 //10 pieces for each player. 2 player game.

typedef struct {
    int x; //Moving right increments this by 1, moving left decrements this by 1.
    int y; //Moving down-right increments this by 1, moving up-left decrements this by 1
} HexPos;

#define INVALID_POSITION() ((HexPos){9, 9})

typedef struct {
    char player; //It can have '.' representing empty cell or be occupied by Player: 'R', 'B'
    HexPos pos;  //pos will be represented by the x and y coordinates on the hexagonal grid
} Cell;

typedef struct {
    Cell cells[MAX_CELLS]; //The board is basically represented as an array of 81 cells.
} Board;

void initializeBoard(Board* board);
int getCellIndex(Board board, HexPos p);

#endif 