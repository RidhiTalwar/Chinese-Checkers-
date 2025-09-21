#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "board.h"
#include "view.h"
#include "utils.h"
#include "move.h"
#include "player.h"
#include "ai.h"

int main() {
    Board board;
    initializeBoard(&board); //Initializing the board
    int playerNum;
    bool isAI = false;
    do {
        printf("Enter 0 to play single-player and 1 to player multi-player\n");
        scanf("%d", &playerNum);
    } while (playerNum != 0 && playerNum != 1);

    if (playerNum == 0) {
        isAI = true;
    }

    if (!isAI) {
        printBoard(board); //Printing the initial board
        char currentPlayer = 'R';
        while(true) {
            int fromX, fromY, toX, toY;
            printf("%s Player: Make your move from\n", currentPlayer == 'R'? "Red" : "Blue");
            scanf("%d", &fromX);
            scanf("%d", &fromY);
            HexPos from, to;
            from.x = fromX;
            from.y = fromY;
            printf("%s Player: Make your move to\n", currentPlayer == 'R'? "Red" : "Blue");
            scanf("%d", &toX);
            scanf("%d", &toY);
            to.x = toX;
            to.y = toY;
            Move move;
            move.from = from;
            move.to = to;
            if (isValidMove(board, move, currentPlayer)) {
            makeMove(&board, move, currentPlayer);
            } else {
                printf("Invalid move. Try again.\n");
                continue;
            }
            printBoard(board);
            if (hasWon(board, currentPlayer)) {
                printf("%s Player has won the game!\n", currentPlayer == 'R' ? "Red" : "Blue");
                break;
            }
            //If current player hasn't won despite the latest move, switch player
            switchPlayer(&currentPlayer);
        }
    }

    if (isAI) {
        char userChar;
        do {
            printf("Enter 'R' to be allotted Red and 'B' to be allotted Blue\n");
            scanf(" %c", &userChar);
        } while (userChar != 'R' && userChar != 'B');
        printBoard(board); //Printing the initial board
        while(true) {
            int fromX, fromY, toX, toY;
            printf("%s Player: Make your move from\n", userChar == 'R'? "Red" : "Blue");
            scanf("%d", &fromX);
            scanf("%d", &fromY);
            HexPos from, to;
            from.x = fromX;
            from.y = fromY;
            printf("%s Player: Make your move to\n", userChar == 'R'? "Red" : "Blue");
            scanf("%d", &toX);
            scanf("%d", &toY);
            to.x = toX;
            to.y = toY;
            Move move;
            move.from = from;
            move.to = to;
            if (isValidMove(board, move, userChar)) {
                makeMove(&board, move, userChar);
            } else {
                printf("Invalid move. Try again.\n");
            continue;
            }
            printBoard(board);
            if (hasWon(board, userChar)) {
                printf("You have won! Congratulations!");
                break;
            }
            printf("The computer is making its move\n");
            int sleep_time = 2;
            sleep(sleep_time);
            Move allMoves[MAX_MOVES];
            int depth = 2;
            char charAllottedToComputer = (userChar == 'R') ? 'B' : 'R';
            Move bestComputerMove = returnBestMove(board, allMoves, charAllottedToComputer, depth);
            makeMove(&board, bestComputerMove, charAllottedToComputer);
            printBoard(board);
            if (hasWon(board, charAllottedToComputer)) {
                printf("You have lost! Condolences!");
                break;
            }
        }
    }
    return 0;
}