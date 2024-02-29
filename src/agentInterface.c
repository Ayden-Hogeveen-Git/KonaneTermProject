#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "konane.h"
#include "minimaxAgent.h"


void setPlayersTurn(GameState* game, char player) {
    if (player == 'B') {
        game->turn = BLACK;
        game->maxPlayer = BLACK;
        game->minPlayer = WHITE;
    }
    else if (player == 'W') {
        game->turn = WHITE;
        game->maxPlayer = WHITE;
        game->minPlayer = BLACK;
    }
    else {
        printf("Invalid player\n");
        exit(1);
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

GameState* initalizeGameState(char* gameString, char player) {
    // Allocate memory for the new game
    GameState* newGame = malloc(sizeof(GameState));

    // Check if memory allocation failed or not
    if (newGame == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Format the game string
    char* gameStringFormatted = formatGameString(gameString);

    // Initialize the game board
    for (int y = 8; y > 0; y--) {
        for (int x = 0; x < 8; x++) {
            // Convert the character to a piece
            if (gameStringFormatted[(8 - y) * 8 + x] == 'B') {
                // newGame->board[y - 1][x].piece = BLACK;
                newGame->board[y - 1][x] = BLACK;
            }
            else if (gameStringFormatted[(8 - y)*8 + x] == 'W') {
                // newGame->board[y - 1][x].piece = WHITE;
                newGame->board[y - 1][x] = WHITE;
            }
            else if (gameStringFormatted[(8 - y)*8 + x] == 'O') {
                // newGame->board[y - 1][x].piece = EMPTY;
                newGame->board[y - 1][x] = EMPTY;
            }
            else if (gameStringFormatted[(8 - y)*8 + x] == '\0') {
                break;
            }
            else {
                printf("Invalid character in game string\n");
                exit(1);
            }

            // // Set the position of the piece
            // newGame->board[y - 1][x].position.x = x;
            // newGame->board[y - 1][x].position.y = y;
        }
    }

    // Set the player's turn
    setPlayersTurn(newGame, player);

    // Set the winner to empty
    newGame->winner = EMPTY;

    // Free the memory
    free(gameStringFormatted);

    // Return the new game
    return newGame;
}

void agentOutput(Move move) {
	// If the start and end coordinates are the same, then it's a first move
	if (move.start.x == move.end.x && move.start.y == move.end.y) {
		printf("%c%d\n", move.start.x, move.start.y);
	}

	// Otherwise, it's a regular move
	else {
		printf("%c%d-%c%d\n", move.start.x, move.start.y, move.end.x, move.end.y);
	}
}

int main(int argc, char* argv[]) {
    // Check if the user provided a file and whose turn it is
    if (argc != 3) {
        fprintf(stderr, "Error: Incorrect number of arguments. Usage: %s <filename> <B|W>\n", argv[0]);
        return 1;
    }

    // Check if the second argument is a valid file
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", argv[1]);
        return 1;
    }

    // Check if the third argument is a valid player
    if (argv[2][0] != 'B' && argv[2][0] != 'W') {
        fprintf(stderr, "Error: Invalid player '%s'. Must be either 'B' or 'W'.\n", argv[2]);
        return 1;
    }

    // Initialize the game string
    char* gameStateString = malloc(72); // 64 (8 x 8) + 7 newline characters + 1 null terminator
    if (gameStateString == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Read all lines of the game from the file, including the newline characters
    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            gameStateString[i] = c;
            i++;
        }
    }

    // Add the null terminator to the end of the string
    gameStateString[i] = '\0';

    // Close the file
    if (file != NULL) {
        fclose(file);
    }

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



    // Initialize the game state 
    GameState* game = initalizeGameState(gameStateString, *argv[2]);

    // Free the memory
    free(gameStateString);

    // Enter the game loop
    while (game->winner == EMPTY) {
        // Get the next move
        Move move = minimaxAlphaBeta(game);
        // Move move = minimaxNew(game);
        // Move move = minimax(game);

        // Make the move
        makeMove(game, move);

        // Output the move
        agentOutput(move);

        // // Print the game board
        // printBoard(game);

        // Scan stdin for the next move
        char* nextMoveString = malloc(6); // 5 characters + 1 null terminator
        if (nextMoveString == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        // Read the next move from stdin
        scanf("%s", nextMoveString);

        // Clear the input buffer
        while ((getchar()) != '\n');

        // Parse the next move in to a Move struct
        Move nextMove;
        if (nextMoveString[2] == '-') {
            nextMove.start.x = nextMoveString[0];
            nextMove.start.y = nextMoveString[1] - '0';
            nextMove.end.x = nextMoveString[3];
            nextMove.end.y = nextMoveString[4] - '0';
        } else {
            nextMove.start.x = nextMoveString[0];
            nextMove.start.y = nextMoveString[1] - '0';
            nextMove.end.x = nextMoveString[0];
            nextMove.end.y = nextMoveString[1] - '0';
        }

        // Make the next move
        makeMove(game, nextMove);

        // // Print the game board
        // printBoard(game);

        // Free the memory
        free(nextMoveString);
    }

    // Free the memory
    free(game);

    return 0;
}