#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>
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
        fprintf(stderr, "Error: Invalid player\n");
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
        fprintf(stderr, "Error: Memory allocation allocation failed\n");
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
        fprintf(stderr, "Error: Memory allocation allocation failed\n");
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
                fprintf(stderr, "Error: Invalid character in game string\n");
                exit(1);
            }
        }
    }
    
    // Check if it's a first move
    if (isFirstMove(newGame)) {
        newGame->firstMove = 1;
    }
    else {
        newGame->firstMove = 0;
    }

    // Set the player's turn
    setPlayersTurn(newGame, player);

    // Set the max and min players
    if (newGame->turn == BLACK) {
        newGame->maxPlayer = BLACK;
        newGame->minPlayer = WHITE;
    }
    else if (newGame->turn == WHITE) {
        newGame->maxPlayer = WHITE;
        newGame->minPlayer = BLACK;
    }

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

Move getOpponentsMove(GameState* game, char* nextMoveString) {
    // Read the next move from stdin
    if (scanf("%s", nextMoveString) != 1) {
        fprintf(stderr, "Error: Could not read next move from stdin.\n");
        exit(1);
    }

    // Clear the input buffer
    while ((getchar()) != '\n');

    // Convert the coordinates to uppercase
    coordToUpper(nextMoveString);

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

    // Return the next move
    return nextMove;
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
        fprintf(stderr, "Error: Memory allocation allocation failed\n");
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

    // Initialize the game state 
    GameState* game = initalizeGameState(gameStateString, *argv[2]);

    // Free the memory
    free(gameStateString);

    // Allocate memory for the next move string
    char* nextMoveString = malloc(6); // 5 characters + 1 null terminator
    if (nextMoveString == NULL) {
        fprintf(stderr, "Error: Memory allocation allocation failed\n");
        return 1;
    }

    // Open the log file
    FILE *logFile = fopen("../test/.log.txt", "a");

    // Check if the file was opened successfully
    if (logFile == NULL) {
        fprintf(stderr, "Error: Could not open log file.\n");
        return 1;
    }

    // Initialize the bestMove
    Move bestMove = { .start = { .x = 'A', .y = -1 }, .end = { .x = 'A', .y = -1 } };

    // Enter the main game loop
    while (game->winner == EMPTY) {
        // Allocate memory for the root node
        Node* node = malloc(sizeof(Node));

        // Check if memory was allocated
        if (node == NULL) {
            fprintf(stderr, "Error: Memory not allocated for node\n");
            exit(1);
        }

        // Initialize the node
        node->game = *game;
        node->capacity = 10;
        node->size = 0;
        // node->value = 0;

        // Allocate memory for the children array
        node->children = malloc(node->capacity * sizeof(Node*));

        // Check if memory was allocated
        if (node->children == NULL) {
            fprintf(stderr, "Error: Memory not allocated for children\n");
            exit(1);
        }

        // Generate the children
        generateChildren(node);

        // Generate the tree of children
        generateTree(node, MAX_DEPTH);

        // Get the next move using minimax or minimaxAlphaBeta
        #ifdef ALPHA_BETA
            minimaxAlphaBeta(node, MAX_DEPTH, INT_MIN, INT_MAX, &bestMove);
        #else
            minimax(node, MAX_DEPTH, &bestMove);
        #endif

        // // Initialize the clock
        // clock_t start_mm, end_mm, start_mmab, end_mmab;
        // double cpu_time_mm, cpu_time_mmab;

        // start_mm = clock();

        // // Get the next move
        // minimax(game);

        // // Stop the clock
        // end_mm = clock();

        // // Log the time taken to compute the move
        // cpu_time_mm = ((double) (end_mm - start_mm)) / CLOCKS_PER_SEC;
        // fprintf(logFile, "minimax() computation time: %f\n", cpu_time_mm);

        // // Start the clock
        // start_mmab = clock();

        // // Get the next move
        // Move move1 = minimaxAlphaBeta(game);

        // // Stop the clock
        // end_mmab = clock();

        // // Log the time taken to compute the move
        // cpu_time_mmab = ((double) (end_mmab - start_mmab)) / CLOCKS_PER_SEC;
        // fprintf(logFile, "minimaxAlphaBetaNew() computation time: %f\n", cpu_time_mmab);

        // // Log the delta between the two algorithms
        // double delta = cpu_time_mm - cpu_time_mmab;
        // fprintf(logFile, "Delta (minimax - minimaxAlphaBeta): %f\n", delta);
        // fprintf(logFile, "Alpha-Beta Pruning is %f percent faster than Minimax\n", (delta / cpu_time_mm) * 100);
        // fprintf(logFile, "====================================================\n");


        // Make the move
        makeMove(game, bestMove);

        // // Check for a winner
        // checkForWinner(game);
        // if (game->winner != EMPTY) {
        //     break;
        // }

        // Output the move to stdout
        agentOutput(bestMove);

        // Get the opponent's move
        Move nextMove = getOpponentsMove(game, nextMoveString);

        // Make the next move
        makeMove(game, nextMove);

        // // Check for a winner
        // checkForWinner(game);
        // if (game->winner != EMPTY) {
        //     break;
        // }

        // Free the memory
        for (int i = 0; i < node->size; i++) {
            free(node->children[i]);
        }
        free(node->children);
        free(node);
    }

    // Print the winner
    if (game->winner == BLACK) {
        printf("BLACK wins!\n");
    } else if (game->winner == WHITE) {
        printf("WHITE wins!\n");
    } else {
        printf("It's a draw!\n");
    }

    // Close the log file
    if (logFile != NULL) {
        fclose(logFile);
    }

    // Free the memory
    free(nextMoveString);
    free(game);

    return 0;
}
