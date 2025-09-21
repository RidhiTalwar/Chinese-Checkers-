#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "ai.h"

int allPossibleMoves(Board board, Move* allMoves, char currentPlayer) {
    /*
    This function does the following steps:-
    - It finds all 10 pieces of a particular player on the board
    - For each piece, it devises a move from its position to every other empty position on the board (61 empty positions => 61 possible moves)
    - Out of these 610 moves, it only adds those those to the array that are valid. Validity is checked via the isValid function
    - It finally returns the number of valid moves found for all pieces of that particular player
    - In addition, it has also initialized the allMoves array to hold all these possible moves
    */
    int movesNum = 0;
    for(int i = 0; i < MAX_CELLS; i++) {
        if (board.cells[i].player == currentPlayer) {
            Move move;
            move.from = board.cells[i].pos;
            for(int j = 0; j < MAX_CELLS; j++) {
                if (board.cells[j].player == '.') {
                    move.to = board.cells[j].pos;
                    if (isValidMove(board, move, currentPlayer)) {
                        allMoves[movesNum++] = move;
                    }
                }
            }
        }
    }
    return movesNum;
}

int evaluateBoard(Board board, char maximizingPlayer) {
    /*
    The purpose of this function is that we give it a board and it gives that board a score representing in how good a position the maximizing player is.
    - It first initializes the sum of 'B' and 'R' players to 0.
    - Then it loops through the board and in redSum, it stores the sum of y coordinates of the positions of each of the 'R' pieces
      and in blueSum, it stores the sum of y coordinates of the positions of each of the 'B' pieces.
    - Then if it's trying to evaluate the score of 'R', it does so via redSum + blueSum. The reasoning for this is below.
    - If it's trying to evaluate the score of 'B', it does so via -(redSum + blueSum). The reasoning for this is below as well.
    - The higher the score, the better the board is looking for the maximizingPlayer and the worse it is looking for the other player, and vice-versa.
    */
    int redSum = 0;
    int blueSum = 0;

    for (int j = 0; j < MAX_CELLS; j++) {
        if (board.cells[j].player == 'R') {
            redSum += board.cells[j].pos.y;
        } else if (board.cells[j].player == 'B') {
            blueSum += board.cells[j].pos.y;
        }
    }

    if (maximizingPlayer == 'R') {
        //The higher the score for red is => closer red is to the bottom => better for winning
        //The higher the score for blue is => closer blue is to the bottom => better for losing
        return redSum + blueSum;
    } else {
        //The lower the score for blue is => closer blue is to the top => better for winning
        //The lower the score for red is => closer red is to the top => better for losing
        return -(blueSum + redSum);
    }
}

int minimax(Board board, int depth, bool isMaximizing, char charAllottedToComputer) {
    /*
    This is the core recursive function behind the Minimax algorithm.
    Here's what it does:
    - First, it checks the base case: if depth is 0 OR someone has already won (either the computer or the opponent),
      then this is a terminal state, so we return the evaluated score of the board using evaluateBoard().
    - Then, depending on whether it's the maximizing player's turn or the minimizing player's turn, we:
        - Generate all possible valid moves for that player.
        - Simulate each move one by one by creating a temporary copy of the board and applying the move.
        - Call minimax again recursively, decreasing the depth by 1 and flipping the isMaximizing flag.
    - If it's the maximizing player (computer), we try to maximize the score.
    - If it's the minimizing player (human), we try to minimize the score.
    - Eventually, we return the best possible score that can be achieved from the current board position
      assuming both players play optimally.
    */
    if (depth == 0 || hasWon(board, charAllottedToComputer) || hasWon(board, (charAllottedToComputer == 'R' ? 'B' : 'R'))) {
        return evaluateBoard(board, charAllottedToComputer);
    }

    Move allMoves[MAX_MOVES];
    char currentPlayer = isMaximizing ? charAllottedToComputer : (charAllottedToComputer == 'R' ? 'B' : 'R');
    int moveCount = allPossibleMoves(board, allMoves, currentPlayer);

    int bestScore = isMaximizing ? INT_MIN : INT_MAX;

    for (int i = 0; i < moveCount; i++) {
        Board newBoard = board;
        makeMove(&newBoard, allMoves[i], currentPlayer);
        int score = minimax(newBoard, depth - 1, !isMaximizing, charAllottedToComputer);

        if (isMaximizing) {
            if (score > bestScore) bestScore = score;
        } else {
            if (score < bestScore) bestScore = score;
        }
    }

    return bestScore;
}

Move returnBestMove(Board board, Move* allMoves, char currentPlayer, int depth) {
    /*
    This function is responsible for actually choosing the best move for the computer to make.
    - First, it generates all valid moves for the current player (computer) using allPossibleMoves().
    - Then, it simulates each of those moves one by one:
        - Creates a copy of the board and makes the move on that copy.
        - Calls the minimax function on that new board, reducing depth and switching to minimizing mode
          (because now it's the opponent's turn).
        - Stores the score returned by minimax.
        - Keeps track of the move with the highest score (i.e., the best move for the computer to make).
    - Finally, returns that move as the best move for the computer to make.
    - This is what gets called inside main() when the computer is deciding what to do.
    */
    int moveCount = allPossibleMoves(board, allMoves, currentPlayer);
    int bestScore = INT_MIN;
    Move bestMove = allMoves[0];
    for (int i = 0; i < moveCount; i++) {
        Board boardCopy = board;
        makeMove(&boardCopy, allMoves[i], currentPlayer);
        int score = minimax(boardCopy, depth - 1, false, currentPlayer);  // opponent's turn next
        if (score > bestScore) {
            bestScore = score;
            bestMove = allMoves[i];
        }
    }
    return bestMove;
}
