#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
// #include "konane.h"

void makeMove(Board* board, char x, int y, char newX, int newY) {
    board->board[newX][newY] = board->board[x][y];
    board->board[x][y] = ' ';
    board->board[(x + newX) / 2][(y + newY) / 2] = ' ';
}

int isValidMove(Board* board, char x, int y, int newX, int newY) {
    if (newX < 'A' || newX > 'H' || newY < 1 || newY > 8) {
        return 0;
    }
    if (abs(newX - x) != 2 && abs(newY - y) != 2) {
        return 0;
    }
    return 1;
}

void addValidMove(ValidMoves* validMoves, char x, int y, char newX, int newY) {
    // If the valid moves array is full, double the capacity
    if (validMoves->size == validMoves->capacity) {
        validMoves->capacity *= 2;
        validMoves->moves = realloc(validMoves->moves, validMoves->capacity * sizeof(Move));
    }

    // Add the valid move to the array
    validMoves->moves[validMoves->size].start.x = x;
    validMoves->moves[validMoves->size].start.y = y;
    validMoves->moves[validMoves->size].end.x = newX;
    validMoves->moves[validMoves->size].end.y = newY;
    validMoves->size++;
}

ValidMoves findValidMoves(Board* board) {
    // Initialize the valid moves array
    ValidMoves validMoves;
    validMoves.capacity = 10;

    // Allocate memory for valid moves array
    validMoves.moves = malloc(validMoves.capacity * sizeof(Move));
    
    // Check if memory allocation failed or not
    if (validMoves.moves == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize valid moves array
    validMoves.size = 0;

    // Find valid moves
    int index = 0;
    for (char x='A'; x<='H'; x++) {
        for (int y=0; y<8; y++) {
            if (board->board[x][y] == 'B') {
                if (isValidMove(board, x, y, x+2, y) == 1) {
                    addValidMove(&validMoves, x, y, x+2, y);
                    index++;
                }
                if (isValidMove(board, x, y, x-2, y) == 1) {
                    addValidMove(&validMoves, x, y, x-2, y);
                    index++;
                }
                if (isValidMove(board, x, y, x, y+2) == 1) {
                    addValidMove(&validMoves, x, y, x, y+2);
                    index++;
                }
                if (isValidMove(board, x, y, x, y-2) == 1) {
                    addValidMove(&validMoves, x, y, x, y-2);
                    index++;
                }
            }
        }
    }

    // Return valid moves array
    return validMoves;
}

Move minimax(Board* board) {
    // Find valid moves
    ValidMoves validMoves = findValidMoves(board);

    // Initialize best move index
    int bestMoveIndex = -1;

    // Initialize max and min values
    // Max (this agent) wants to maximize the total number of valid moves
    // Min (opponent) wants to minimize the total number of valid moves
    int max = -1000; // Max is initialized to negative infinity
    int min = 1000; // Min is initialized to positive infinity

    // Loop through valid moves
    for (int i=0; i<validMoves.size; i++) {
        
        // Implement the minmax algorithm

    // Return best move
    return validMoves.moves[bestMoveIndex];
}
