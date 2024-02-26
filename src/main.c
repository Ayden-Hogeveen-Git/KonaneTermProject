#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "konane.h"
#include "minimaxAgent.h"


int main() {
    // Game Variables
    int running = 1; 
    Point firstMoveBlack, firstMoveWhite;  // Coordinates of the first two moves

    // Initialize the game board
    Board board;
    initializeBoard(&board);

    // Print out the initial board
    printf("Initial board:\n");
    printBoard(board);

    // Get the first move for black
    while (1) {
        printf("BLACK's move:\n");
        printf("Enter the 'X' and 'Y' coordinates of the piece you want to remove: ");
        scanf(" %c %d", &firstMoveBlack.x, &firstMoveBlack.y);

        // Convert the coordinates to uppercase
        toUpper(&firstMoveBlack.x);

        // Check if the move is valid, if so, break the loop
        if (isValidFirstMove(&board, firstMoveBlack) == 1) {
            break;
        }

        // Print an error message
        printf("Invalid move, BLACK can only remove D5 or E4.\n");
    }

    // Make the first move for black and print the board
    makeFirstMove(&board, firstMoveBlack);

    // Print out the move and the updated board
    printf("BLACK removes %c%d\n", firstMoveBlack.x, firstMoveBlack.y);
    printBoard(board);

    // Toggle the player's turn
    board.player = MINIMIZING_PLAYER;

    // Get the first move for white
    while (1) {
        printf("WHITE's move:\n");
        printf("Enter the 'X' and 'Y' coordinates of the piece you want to remove: ");
        scanf(" %c %d", &firstMoveWhite.x, &firstMoveWhite.y);

        // Convert the coordinates to uppercase
        toUpper(&firstMoveWhite.x);

        // Check if the move is valid, if so, break the loop
        if (isValidFirstMove(&board, firstMoveWhite) == 1) {
            break;
        }

        // Print an error message
        printf("Invalid move, WHITE can only remove D4 or E5.\n");
    }

    // Make the first move for white and print the board
    makeFirstMove(&board, firstMoveWhite);

    // Print out the move and the updated board
    printf("WHITE removes %c%d\n", firstMoveWhite.x, firstMoveWhite.y);
    printBoard(board);

    // Toggle the player's turn
    board.player = MAXIMIZING_PLAYER;

    // Main Game Loop
    while (running == 1) {
        // Initialize move
        Move move;

        // Get the next move
        if (board.player == MAXIMIZING_PLAYER) {
            printf("BLACK's move:\n");
            move = minimax(&board);
            printf("minimax... BLACK moves from %c%d to %c%d\n", move.start.x, move.start.y, move.end.x, move.end.y);
        } else if (board.player == MINIMIZING_PLAYER) {
            printf("WHITE's move:\n");
            printf("Enter the 'X' and 'Y' coordinates of the piece you want to move: ");
            scanf("%c %d", &move.start.x, &move.start.y);
            printf("Enter the 'X' and 'Y' coordinates of the new position: ");
            scanf("%c %d", &move.end.x, &move.end.y);

            // Convert the coordinates to uppercase
            toUpper(&move.start.x);
            toUpper(&move.end.x);
        }

        // Check if move is valid
        if (isValidMove(&board, move) == 0) {
            printf("Invalid move\n");
        } else {
            makeMove(&board, move);
            printBoard(board);
            board.player = (board.player == MAXIMIZING_PLAYER) ? MINIMIZING_PLAYER : MAXIMIZING_PLAYER;
        }

        // Check if the game is over
        if (findValidMoves(&board).size == 0) {
            running = 0;
        }
    }
}
