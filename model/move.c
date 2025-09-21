#include <stdio.h>
#include <stdlib.h>
#include "move.h"
#include <stdbool.h>
#include "utils.h"
#include "board.h"

bool canReach(Board board, HexPos current, HexPos target, bool visited[MAX_CELLS]) {
    /*
    This function checks if a piece can reach a certain target position from its current position via jumps only.
    So this function allows multi-step jumps — as long as the jumping rules are followed — and returns true if there's any valid path of jumps from current to target.
    */
    int currentIndex = getCellIndex(board, current);

    if (currentIndex == -1 || visited[currentIndex]) return false;
    //It first checks if the current position is valid and hasn’t already been visited in this chain of jumps (to avoid infinite loops).

    visited[currentIndex] = true;
    if (current.x == target.x && current.y == target.y) return true;
    //If the current position is the target, it returns true — we’ve reached the destination.

    // Get all valid neighbors
    HexPos neighbors[MAX_NEIGHBORS];
    getNeighbors(current, neighbors);

    /*
    For each neighbor (which represents a potential "middle" piece we can jump over), it:
    - Computes the landing position based on jump rules.
    - Checks if the landing position is valid, unoccupied, and on the board.
    - Then recursively calls canReach on that landing position, continuing the jump chain.
    */
    for (int i = 0; i < MAX_NEIGHBORS; i++) {
        HexPos mid = neighbors[i];
        int midIndex = getCellIndex(board, mid);

        // If the middle cell is invalid or empty, skip it
        if (midIndex == -1 || board.cells[midIndex].player == '.') continue;

        // Compute landing position = current + 2 * (mid - current)
        HexPos landing;
        landing.x = current.x + 2 * (mid.x - current.x);
        landing.y = current.y + 2 * (mid.y - current.y);

        int landingIndex = getCellIndex(board, landing);

        if (!isValidPosition(landing) || landingIndex == -1) continue;
        if (board.cells[landingIndex].player != '.') continue;

        // Recurse on the landing position
        if (canReach(board, landing, target, visited)) return true;
    }

    return false;
}

bool isValidMove(Board board, Move move, char currentPlayer) {
    /*
    Checks if a move is valid according to rules of Chinese Checkers. Specific cases are explained below.
    */
    int fromIndex = getCellIndex(board, move.from);
    int toIndex = getCellIndex(board, move.to);

    //If we try to move piece to or from invalid position
    if (fromIndex == -1 || toIndex == -1) {
        return false;
    }

    //To make sure the player only tried to move the correct piece
    if (board.cells[fromIndex].player != currentPlayer) {
        return false;
    }

    //To make sure he does move the piece somewhere
    if(move.from.x == move.to.x && move.from.y == move.to.y) {
        return false;
    }

    //To make sure that the place being moved to is empty to begin with
    if(board.cells[toIndex].player != '.') {
        return false;
    }

    //To allow moving to adjacent places
    if (isNeighbor(move.from, move.to)) {
        return true;
    }

    //If the piece tries to jump, check the validity of the single or multi jump
    bool visited[MAX_CELLS] = {false};
    return canReach(board, move.from, move.to, visited);
}

void makeMove(Board* boardPointer, Move move, char currentPlayer) {
    /*
    If the move has been validated, this function updates the board to store the move.
    - It makes the cell corresponding to the starting(from) position store '.', essentially emptying it.
    - It updates the cell corresponding to the ending(to) position store the piece we're trying to move, essentially storing the move.
    */
    int fromIndex = getCellIndex(*boardPointer, move.from);
    int toIndex = getCellIndex(*boardPointer, move.to);
    boardPointer->cells[toIndex].player = currentPlayer;
    boardPointer->cells[fromIndex].player = '.';
}