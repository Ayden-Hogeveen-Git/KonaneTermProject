#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "konane.h"


int isValidMove(Board* board, char x, int y, int newX, int newY) {
    if (newX < 'A' || newX > 'H' || newY < 1 || newY > 8) {
        return 0;
    }
    if (abs(newX - x) != 2 && abs(newY - y) != 2) {
        return 0;
    }
    return 1;
}

Move* findValidMoves(Board* board) {
    // Allocate memory for valid moves array
    Move* validMoves = (Move*) malloc(sizeof(Move) * 32); // Start with 32 possible moves, realloc later if needed
    
    // Check for if memory allocation failed or not
    if (validMoves == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize valid moves array
    for (int i=0; i<64; i++) {
        validMoves[i].start.x = -1;
        validMoves[i].start.y = -1;
        validMoves[i].end.x = -1;
        validMoves[i].end.y = -1;
    }

    // Find valid moves
    int index = 0;
    for (char x='A'; x<='H'; x++) {
        for (int y=0; y<8; y++) {
            if (board->board[x][y] == 'B') {
                if (isValidMove(board, x, y, x+2, y) == 1) {
                    validMoves[index].start.x = x;
                    validMoves[index].start.y = y;
                    validMoves[index].end.x = x+2;
                    validMoves[index].end.y = y;
                    index++;
                }
                if (isValidMove(board, x, y, x-2, y) == 1) {
                    validMoves[index].start.x = x;
                    validMoves[index].start.y = y;
                    validMoves[index].end.x = x-2;
                    validMoves[index].end.y = y;
                    index++;
                }
                if (isValidMove(board, x, y, x, y+2) == 1) {
                    validMoves[index].start.x = x;
                    validMoves[index].start.y = y;
                    validMoves[index].end.x = x;
                    validMoves[index].end.y = y+2;
                    index++;
                }
                if (isValidMove(board, x, y, x, y-2) == 1) {
                    validMoves[index].start.x = x;
                    validMoves[index].start.y = y;
                    validMoves[index].end.x = x;
                    validMoves[index].end.y = y-2;
                    index++;
                }
            }
        }
    }

    // Return valid moves array
    return validMoves;
}

Move minimax(Board* board) {

}
