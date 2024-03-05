#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "konane.h"
#include "minimaxAgent.h"


int main() {
    // Game Variables
    int running = 1; 
    Point firstMoveBlack, firstMoveWhite;  // Coordinates of the first two moves


    // // Define a default new game string
    // const char *defaultGameString = "BWBWBWBW"
    //                                 "WBWBWBWB"
    //                                 "BWBWBWBW"
    //                                 "WBWBWBWB"
    //                                 "BWBWBWBW"
    //                                 "WBWBWBWB"
    //                                 "BWBWBWBW"
    //                                 "WBWBWBWB";

    // // Copy the default game string to the game string
    // strcpy(gameStateString, defaultGameString);


    // Initialize the game
    GameState* game = initializeGameState();

    // Print out the initial game
    printf("Initial game:\n");
    printBoard(game);

    // Get the first move for black
    while (1) {
        // Get a valid first move for black
        printf("BLACK's move:\n");
        printf("Enter the 'X' and 'Y' coordinates of the piece you want to remove: ");
        if (scanf(" %c %d", &firstMoveBlack.x, &firstMoveBlack.y) != 2) {
            printf("Invalid input\n");
            continue;
        }

        // Clear the input buffer
        while ((getchar()) != '\n');

        // Convert the coordinates to uppercase
        coordToUpper(&firstMoveBlack.x);

        // Check if the move is valid, if so, break the loop
        if (isValidFirstMove(game, firstMoveBlack) == 1) {
            break;
        }

        // Print an error message
        printf("Invalid move, BLACK can only remove D5 or E4.\n");
    }

    // Make the first move for black and print the game
    makeFirstMove(game, firstMoveBlack);

    // Print out the move and the updated game
    printf("BLACK removes %c%d\n", firstMoveBlack.x, firstMoveBlack.y);
    printBoard(game);

    // Get the first move for white
    while (1) {
        // Get a valid first move for white
        printf("WHITE's move:\n");
        printf("Enter the 'X' and 'Y' coordinates of the piece you want to remove: ");
        if (scanf(" %c %d", &firstMoveWhite.x, &firstMoveWhite.y) != 2) {
            printf("Invalid input\n");
            continue;
        }

        // Clear the input buffer
        while ((getchar()) != '\n');

        // Convert the coordinates to uppercase
        coordToUpper(&firstMoveWhite.x);

        // Check if the move is valid, if so, break the loop
        if (isValidFirstMove(game, firstMoveWhite) == 1) {
            break;
        }

        // Print an error message
        printf("Invalid move, WHITE can only remove D4 or E5.\n");
    }

    // Make the first move for white and print the game
    makeFirstMove(game, firstMoveWhite);

    // Print out the move and the updated game
    printf("WHITE removes %c%d\n", firstMoveWhite.x, firstMoveWhite.y);
    printBoard(game);

    // Main Game Loop
    while (running == 1) {
        // Initialize move
        Move move;

        // Get the next move
        if (game->turn == BLACK) {
            printf("BLACK's move:\n");
            // move = minimax(&game);
            // printf("minimax... BLACK moves from %c%d to %c%d\n", move.start.x, move.start.y, move.end.x, move.end.y);
            // move = minimaxAlphaBeta(game);
            printf("minimaxAlphaBeta... BLACK moves from %c%d to %c%d\n", move.start.x, move.start.y, move.end.x, move.end.y);
        } else if (game->turn == WHITE) {
            // Get a valid start move for white
            printf("WHITE's move:\n");
            printf("Enter the 'X' and 'Y' coordinates of the piece you want to move: ");
            if (scanf("%c %d", &move.start.x, &move.start.y) != 2) {
                printf("Invalid input\n");
                continue;
            }

            // Clear the input buffer
            while ((getchar()) != '\n');

            // Get a valid end move for white
            printf("Enter the 'X' and 'Y' coordinates of the new position: ");
            if (scanf("%c %d", &move.end.x, &move.end.y) != 2) {
                printf("Invalid input\n");
                continue;
            }

            // Clear the input buffer
            while ((getchar()) != '\n');

            // Convert the coordinates to uppercase
            coordToUpper(&move.start.x);
            coordToUpper(&move.end.x);
        }

        // // Check if move is valid
        // if (isValidMove(game, move) == 0) {
        //     printf("Invalid move\n");
        // } else {
        //     makeMove(game, move);
        //     printBoard(game);
        // }

        // Check if the game is over
        if (game->winner != EMPTY) {
            running = 0;
            // Print the winner
            if (game->winner == BLACK) {
                printf("BLACK wins!\n");
            } else if (game->winner == WHITE) {
                printf("WHITE wins!\n");
            } else {
                printf("It's a draw!\n");
            }
            break;
        }

        // ValidMoves validMoves = findValidMoves(&game);
        // if (validMoves.size == 0) {
        //     running = 0;
        //     freeValidMoves(&validMoves);
        //     break;
        // }

        // // Free the memory
        // freeValidMoves(&validMoves);
    }
}
