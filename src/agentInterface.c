#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "konane.h"
#include "minimaxAgent.h"


int whoseTurn(GameState* game) {
    int black = 0;
    int white = 0;

    for (int y = 8; y > 0; y--) {
        for (int x = 0; x < 8; x++) {
            if (game->board[y - 1][x].piece == BLACK) {
                black++;
            }
            else if (game->board[y - 1][x].piece == WHITE) {
                white++;
            }
        }
    }

    if (black == white) {
        return MAXIMIZING_PLAYER;
    }
    else {
        return MINIMIZING_PLAYER;
    }
}

char* formatGameString(char* gameString) {
    // Calculate the length of the gameString, excluding the newline characters
    int length = 0;
    for (int i = 0; gameString[i] != '\0'; i++) {
        if ((gameString[i] >= 'A' && gameString[i] <= 'Z') || (gameString[i] >= 'a' && gameString[i] <= 'z')) {
            length++;
        }
    }

    // Allocate memory for the new game string
    char* newGameString = malloc(length + 1); // +1 for the null terminator

    // Check if memory allocation failed or not
    if (newGameString == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Remove the newline characters from the game string
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (gameString[i] != '\n') {
            newGameString[j] = gameString[i];
            j++;
        }
    }

    // Add the null terminator to the end of the string
    newGameString[j] = '\0';

    return newGameString;
}

GameState* initalizeGame(char* gameString) {
    // Allocate memory for the new game
    GameState* newGame = malloc(sizeof(GameState));

    // Check if memory allocation failed or not
    if (newGame == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Format the game string
    char* newGameString = formatGameString(gameString);

    printf("%s\n", newGameString);


    // Initialize the game board
    for (int y = 8; y > 0; y--) {
        for (int x = 0; x < 8; x++) {
            // Convert the character to a piece
            if (newGameString[(8 - y) * 8 + x] == 'B') {
                newGame->board[y - 1][x].piece = BLACK;
            }
            else if (newGameString[(8 - y)*8 + x] == 'W') {
                newGame->board[y - 1][x].piece = WHITE;
            }
            else if (newGameString[(8 - y)*8 + x] == 'O') {
                newGame->board[y - 1][x].piece = EMPTY;
            }
            else if (newGameString[(8 - y)*8 + x] == '\0') {
                break;
            }
            else {
                printf("Invalid character in game string\n");
                exit(1);
            }

            // Set the position of the piece
            newGame->board[y - 1][x].position.x = x;
            newGame->board[y - 1][x].position.y = y;
        }
    }

    // Determine the player's turn
    int player = whoseTurn(newGame);

    // Set the correct player
    newGame->player = player;

    // Set the winner to empty
    newGame->winner = EMPTY;

    // Free the memory
    free(newGameString);

    // Return the new game
    return newGame;
}

void agentOutput(Move move) {
	// If the start and end coordinates are the same, then it's a first move
	if (move.start.x == move.end.x && move.start.y == move.end.y) {
		printf("%c%d", move.start.x, move.start.y);
	}

	// Otherwise, it's a regular move
	else {
		printf("%c%d-%c%d", move.start.x, move.start.y, move.end.x, move.end.y);
	}
}

int main(int argc, char* argv[]) {
    // Initialize the game string
    char* gameString = malloc(72); // 64 (8 x 8) + 7 newline characters + 1 null terminator
    if (gameString == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Check if the user provided a file
    if (argc == 2) {
        // Initialize the file
        FILE* file;

        // Open the file
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("File not found\n");
            return 1;
        }

        // Read all lines of the game from the file, including the newline characters
        char c;
        int i = 0;
        while ((c = fgetc(file)) != EOF) {
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                gameString[i] = c;
                i++;
            }
        }

        // Add the null terminator to the end of the string
        gameString[i] = '\0';

        // Close the file
        if (file != NULL) {
            fclose(file);
        }

    } else if (argc == 1) {
        // Define a default new game string
        const char* defaultGameString = "BWBWBWBW"
                                        "WBWBWBWB"
                                        "BWBWBWBW"
                                        "WBWBWBWB"
                                        "BWBWBWBW"
                                        "WBWBWBWB"
                                        "BWBWBWBW"
                                        "WBWBWBWB";

        // Copy the default game string to the game string
        strcpy(gameString, defaultGameString);

    } else {
        printf("Usage: %s [file]\n", argv[0]);
        return 1;
    }

    // Initialize the game
    GameState* game = initalizeGame(gameString);

    // printf("%s\n", gameString);
    printBoard(*game);
    // Get the next move
    Move move = minimaxAlphaBeta(game);

    // Output the move
    agentOutput(move);

    // Free the memory
    free(gameString);
    free(game);

    return 0;
}
