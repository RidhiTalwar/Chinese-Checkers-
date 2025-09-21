#include <stdio.h> 
#include <stdlib.h> 
#include "view.h"

// ANSI color escape codes
#define RED   "\x1B[31m"
#define BLUE  "\x1B[34m"
#define RESET "\x1B[0m"

void printBoard(Board board) {
    /*
    This function provides a visual representation of the Chinese Checkers game board (Its diamond as this is a 2-player version of the game)
    - We use loops and format it by adding spaces such that it forms the requisite diamond shape.
    - When a move is made and it is updated in the cells array of the board, the print function is called in main() and reflects the move.
    */
    int count = 0; 
    for(int i = -8; i <= 0; i++) {
        for(int j = 1; j <= abs(i); j++) {
            printf(" ");
        }
        for(int j = 1; j <= i + 9; j++) {
            // Added color handling while keeping original logic
            if (board.cells[count].player == 'R') {
                printf(RED "R " RESET);
            } else if (board.cells[count].player == 'B') {
                printf(BLUE "B " RESET);
            } else {
                printf(". ");
            }
            count++;
        }
        printf("\n");
    }

    for(int i = 1; i <= 8; i++) {
        for(int j = 1; j <= i; j++) {
            printf(" "); 
        }
        for(int j = 0; j < 9 - i; j++) {
            // Added color handling while keeping original logic
            if (board.cells[count].player == 'R') {
                printf(RED "R " RESET);
            } else if (board.cells[count].player == 'B') {
                printf(BLUE "B " RESET);
            } else {
                printf(". ");
            }
            count++;
        }
        printf("\n");
    }
}
