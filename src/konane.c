#include <stdlib.h>
#include <stdio.h>
#include "structures.h"


void printBoard(Board board) {
    printf("\n");
    for (int x=0; x<8; x++) {
        for (int y=0; y<8; y++) {
            printf("%c ", board.state[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

Board* copyBoard(Board* board) {
    // Allocate memory for the new board
    Board* newBoard = malloc(sizeof(Board));

    // Check if memory allocation failed or not
    if (newBoard == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Copy the state of the board
    for (int x=0; x<8; x++) {
        for (int y=0; y<8; y++) {
            newBoard->state[x][y] = board->state[x][y];
        }
    }

    // Return the new board
    return newBoard;
}

void toUpper(char* str) {
    for (int i=0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
}

int isValidFirstMove(Board* board, int playersTurn, Point point) {
    // Convert the x coordinates from A-H to 0-7
    int x = point.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int y = point.y - 1;

    // Check if the start coordinates are within the game starting area
    if (x < 3 || x > 4 || y < 3 || y > 4) {
        return 0;
    }

    // Check if the player is moving their own piece
    if (playersTurn == 0 && board->state[x][y] != 'B') {
        return 0;
    } else if (playersTurn == 1 && board->state[x][y] != 'W') {
        return 0;
    }

    return 1;
}

int isValidMove(Board* board, int playersTurn, Move move) {
    // Convert the x coordinates from A-H to 0-7
    int x = move.start.x - 'A';
    int newX = move.end.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int y = move.start.y - 1;
    int newY = move.end.y - 1;

    // Check if the start coordinates are within the game board
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return 0;
    }

    // Check if the end coordinates are within the game board
    if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
        return 0;
    }

    // Check if the piece is moving to an empty space
    if (board->state[newX][newY] != 'O') {
        return 0;
    }

    // Check if the piece is moving to a valid space
    if (abs(newX - x) != 2 && abs(newY - y) != 2) {
        return 0;
    }

    // Check if the player is moving their own piece
    if (playersTurn == 0 && board->state[x][y] != 'B') {
        return 0;
    } else if (playersTurn == 1 && board->state[x][y] != 'W') {
        return 0;
    }

    return 1;
}

void makeFirstMove(Board* board, Point point) {
    // Convert the x coordinates from A-H to 0-7
    int x = point.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int y = point.y - 1;

    // Make the move
    board->state[x][y] = 'O';
}

void makeMove(Board* board, Move move) {
    // Convert the x coordinates from A-H to 0-7
    int oldX = move.start.x - 'A';
    int newXIndex = move.end.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int oldY = move.start.y - 1;
    int newYIndex = move.end.y - 1;

    // Make the move
    board->state[newXIndex][newYIndex] = board->state[oldX][oldY];
    board->state[oldX][oldY] = 'O';
    board->state[(oldX + newXIndex) / 2][(oldY + newYIndex) / 2] = 'O';
}

void addValidMove(ValidMoves* validMoves, Move move) {
    // If the valid moves array is full, double the capacity
    if (validMoves->size == validMoves->capacity) {
        validMoves->capacity *= 2;
        validMoves->moves = realloc(validMoves->moves, validMoves->capacity * sizeof(Move));
    }

    // Add the valid move to the array
    validMoves->moves[validMoves->size] = move;
    validMoves->size++;
}

ValidMoves findValidMoves(Board* board, int playersTurn) {
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
    for (int x=0; x<8; x++) {
        for (int y=0; y<8; y++) {
            if (board->state[x][y] == 'B') {
                // Check if the piece can move to the left
                Move moveLeft = {{x, y}, {x-2, y}};
                if (isValidMove(board, playersTurn, moveLeft) == 1) {
                    addValidMove(&validMoves, moveLeft);
                    index++;
                }

                // Check if the piece can move to the right
                Move moveRight = {{x, y}, {x+2, y}};
                if (isValidMove(board, playersTurn, moveRight) == 1) {
                    addValidMove(&validMoves, moveRight);
                    index++;
                }

                // Check if the piece can move up
                Move moveUp = {{x, y}, {x, y+2}};
                if (isValidMove(board, playersTurn, moveUp) == 1) {
                    addValidMove(&validMoves, moveUp);
                    index++;
                }

                // Check if the piece can move down
                Move moveDown = {{x, y}, {x, y-2}};
                if (isValidMove(board, playersTurn, moveDown) == 1) {
                    addValidMove(&validMoves, moveDown);
                    index++;
                }
            }
        }
    }

    // Return valid moves array
    return validMoves;
}
