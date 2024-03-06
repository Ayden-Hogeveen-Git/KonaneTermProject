#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "konane.h"


FILE* openLogFile() {
    // Open the log file
    FILE *logFile = fopen("../test/.log.txt", "w");

    // Check if the file was opened successfully
    if (logFile == NULL) {
        fprintf(stderr, "Error: Could not open log file.\n");
        exit(1);
    }

    return logFile;
}

void logString(char* string) {
    // Open the log file
    FILE* logFile = openLogFile();

    // Print the string to the log file
    fprintf(logFile, "%s\n", string);

    // Close the log file
    fclose(logFile);
}

void logStringWithInt(char* string, int value) {
    // Open the log file
    FILE* logFile = openLogFile();

    // Print the string to the log file
    fprintf(logFile, "%s%d\n", string, value);

    // Close the log file
    fclose(logFile);
}

void logStringWithFloat(char* string, float value) {
    // Open the log file
    FILE* logFile = openLogFile();

    // Print the string to the log file
    fprintf(logFile, string, value);

    // Close the log file
    fclose(logFile);
}

void logGameState(GameState* game, Move move) {
    // Open the log file
    FILE* logFile = openLogFile();

    // Print the current player's turn
    fprintf(logFile, "Player's turn: %s\n", game->turn == BLACK ? "WHITE" : "BLACK");
    // Determine which player made the move
    char* player = game->turn == BLACK ? "WHITE" : "BLACK"; // order is reverse since move already toggled player

    // If the start and end coordinates are the same, then it's a first move
    if (move.start.x == move.end.x && move.start.y == move.end.y) {
        fprintf(logFile, "Player %s's first move: %c%d\n", player, move.start.x, move.start.y);
    } else { // Otherwise, it's a regular move
        fprintf(logFile, "Player %s's move: %c%d-%c%d\n", player, move.start.x, move.start.y, move.end.x, move.end.y);
        char* directionString = directionToString(move.direction);
        int directionInt = directionToInt(move.direction);
        fprintf(logFile, "Direction: %s\n", directionString);
        fprintf(logFile, "Direction value: %d\n", directionInt);
        fprintf(logFile, "Jumps: %d\n", move.jumps);
    }

    // Print the game board to the log file
    fprintf(logFile, "  A B C D E F G H\n");
    for (int y = 7; y >= 0; y--) {
        fprintf(logFile, "%d ", y + 1); // Adjust the y coordinate by + 1
        for (int x = 0; x <= 7; x++) {
            fprintf(logFile, "%c ", pieceToChar(game->board[y][x]));
        }
        fprintf(logFile, "%d\n", y + 1); // Adjust the y coordinate by + 1
    }
    fprintf(logFile, "  A B C D E F G H\n\n");

    // Close the log file
    fclose(logFile);
}