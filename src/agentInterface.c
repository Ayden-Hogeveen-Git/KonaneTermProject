#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "structures.h"
#include "konane.h"
#include "minimaxAgent.h"


void logString(char* string) {
    // Open the log file
    FILE *logFile = fopen("../test/.log.txt", "a");

    // Check if the file was opened successfully
    if (logFile == NULL) {
        fprintf(stderr, "Error: Could not open log file.\n");
        exit(1);
    }

    // Print the string to the log file
    fprintf(logFile, "%s\n", string);

    // Close the log file
    fclose(logFile);
}

void logStringWithInt(char* string, int value) {
    // Open the log file
    FILE *logFile = fopen("../test/.log.txt", "a");

    // Check if the file was opened successfully
    if (logFile == NULL) {
        fprintf(stderr, "Error: Could not open log file.\n");
        exit(1);
    }

    // Print the string to the log file
    fprintf(logFile, "%s%d\n", string, value);

    // Close the log file
    fclose(logFile);
}

void logStringWithFloat(char* string, float value) {
    // Open the log file
    FILE *logFile = fopen("../test/.log.txt", "a");

    // Check if the file was opened successfully
    if (logFile == NULL) {
        fprintf(stderr, "Error: Could not open log file.\n");
        exit(1);
    }

    // Print the string to the log file
    fprintf(logFile, string, value);

    // Close the log file
    fclose(logFile);
}

void logGameState(GameState* game, Move move) {
    // Open the log file
    FILE *logFile = fopen("../test/.log.txt", "a");

    // Check if the file was opened successfully
    if (logFile == NULL) {
        fprintf(stderr, "Error: Could not open log file.\n");
        exit(1);
    }

    // Print the current player's turn
    fprintf(logFile, "Player's turn: %s\n", game->turn == BLACK ? "WHITE" : "BLACK");
    // Determine which player made the move
    char* player = game->turn == BLACK ? "WHITE" : "BLACK"; // order is reverse since move already toggled player

    // If the start and end coordinates are the same, then it's a first move
    if (move.start.x == move.end.x && move.start.y == move.end.y) {
        fprintf(logFile, "Player %s's first move: %c%d\n", player, move.start.x, move.start.y);
    } else { // Otherwise, it's a regular move
        fprintf(logFile, "Player %s's move: %c%d-%c%d\n", player, move.start.x, move.start.y, move.end.x, move.end.y);
        fprintf(logFile, "Direction: %s\n", directionToString(move.direction));
        fprintf(logFile, "Direction value: %d\n", directionToInt(move.direction));
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

void setPlayersTurn(GameState* game, char player) {
    // Count the number of empty spaces
    int emptySpaces = countEmptySpaces(game);

    // Set the player's turn
    if (emptySpaces == 0) {
        game->turn = BLACK;
    } else if (emptySpaces == 1) {
        game->turn = WHITE;
    } else {
        if (player == 'B') {
            game->turn = BLACK;
        } else if (player == 'W') {
            game->turn = WHITE;
        } else {
            fprintf(stderr, "Error: Cannot set player's turn. Invalid player\n");
            exit(1);
        }
    }
}

void setMaxAndMinPlayers(GameState* game, Player agentPlayer) {
    if (agentPlayer == BLACK) {
        game->maxPlayer = BLACK;
        game->minPlayer = WHITE;
    }
    else if (agentPlayer == WHITE) {
        game->maxPlayer = WHITE;
        game->minPlayer = BLACK;
    }
    else {
        fprintf(stderr, "Error: Cannot set max and min players. Invalid player\n");
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
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x <= 7; x++) {
            // Convert the character to a piece
            if (gameStringFormatted[(7 - y) * 8 + x] == 'B') {
                newGame->board[y][x] = BLACK;
            }
            else if (gameStringFormatted[(7 - y) * 8 + x] == 'W') {
                newGame->board[y][x] = WHITE;
            }
            else if (gameStringFormatted[(7 - y) * 8 + x] == 'O') {
                newGame->board[y][x] = EMPTY;
            }
            else if (gameStringFormatted[(7 - y) * 8 + x] == '\0') {
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
    setMaxAndMinPlayers(newGame, newGame->turn);

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

    // Determine the move's direction
    if (nextMove.start.x == nextMove.end.x) {
        if (nextMove.start.y < nextMove.end.y) {
            nextMove.direction = UP;
        } else {
            nextMove.direction = DOWN;
        }
    } else if (nextMove.start.y == nextMove.end.y) {
        if (nextMove.start.x < nextMove.end.x) {
            nextMove.direction = RIGHT;
        } else {
            nextMove.direction = LEFT;
        }
    } else if (nextMove.start.x == nextMove.end.x && nextMove.start.y == nextMove.end.y) {
        nextMove.direction = FIRST;
    } else {
        fprintf(stderr, "Error: Invalid move direction\n");
        exit(1);
    }

    // Determine the number of jumps
    if (nextMove.direction == FIRST) {
        nextMove.jumps = 0;
    } else {
        int jumpsX = abs(nextMove.start.x - nextMove.end.x) / 2;
        int jumpsY = abs(nextMove.start.y - nextMove.end.y) / 2;
        nextMove.jumps = jumpsX > 0 ? jumpsX : jumpsY;
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

    // Allocate memory for the next move string
    char* nextMoveString = malloc(6); // 5 characters + 1 null terminator
    if (nextMoveString == NULL) {
        fprintf(stderr, "Error: Memory allocation allocation failed\n");
        return 1;
    }

    // Initialize the bestMove
    Move bestMove = { .start = { .x = 'A', .y = -1 }, .end = { .x = 'A', .y = -1 } };
    
    #ifdef LOGGING
        // Log the game state
        logGameState(game, bestMove);
    #endif

    // Enter the main game loop
    while (game->winner == EMPTY) {
        // Check if there's a winner
        checkForWinner(game);
        if (game->winner != EMPTY) {
            break;
        }

        // Allocate memory for the root node
        Node* node = initializeNode();
        
        // Set the game state
        node->game = *game;

        // Generate the children
        generateChildren(node);

        // Generate the tree of children
        generateTree(node, MAX_TREE_DEPTH);

        #ifdef LOGGING
            // Count the max depth of the minimax tree
            int maxDepth = countTreeDepth(node);

            // Log the depth and number of children
            logStringWithInt("Max Tree Depth: ", maxDepth);
            logStringWithInt("Siblings: ", countSiblings(node));
            logStringWithInt("Total Children: \n", countChildren(node));
        #endif

        // Get the next move using minimax or minimaxAlphaBeta
        #ifdef ALPHA_BETA
            minimaxAlphaBeta(node, MAX_SEARCH_DEPTH, INT_MIN, INT_MAX, &bestMove);
        #else
            minimax(node, MAX_TREE_DEPTH, &bestMove);
        #endif

        #ifdef LOGGING
            // Initialize the clock
            clock_t start_mm, end_mm, start_mmab, end_mmab;
            double cpu_time_mm, cpu_time_mmab;

            start_mm = clock();

            // Get the next move
            minimax(node, MAX_TREE_DEPTH, &bestMove);

            // Stop the clock
            end_mm = clock();

            // Log the time taken to compute the move
            cpu_time_mm = ((double) (end_mm - start_mm)) / CLOCKS_PER_SEC;
            logStringWithFloat("minimax() computation time: %f\n", cpu_time_mm);

            // Start the clock
            start_mmab = clock();

            // Get the next move
            minimaxAlphaBeta(node, MAX_TREE_DEPTH, INT_MIN, INT_MAX, &bestMove);

            // Stop the clock
            end_mmab = clock();

            // Log the time taken to compute the move
            cpu_time_mmab = ((double) (end_mmab - start_mmab)) / CLOCKS_PER_SEC;
            logStringWithFloat("minimaxAlphaBetaNew() computation time: %f\n", cpu_time_mmab);

            // Log the delta between the two algorithms
            double delta = cpu_time_mm - cpu_time_mmab;
            logStringWithFloat("Delta (minimax - minimaxAlphaBeta): %f\n", delta);
            logStringWithFloat("Alpha-Beta Pruning is %f percent faster than Minimax\n", (delta / cpu_time_mm) * 100);
            logString("====================================================\n");
        #endif

        // Make the move
        makeMove(game, bestMove);

        #ifdef LOGGING
            // Log the game state and chose move
            logGameState(game, bestMove);
        #endif

        // Free the memory
        freeTree(node);

        // Output the move to stdout
        agentOutput(bestMove);

        // Get the opponent's move
        Move nextMove = getOpponentsMove(game, nextMoveString);

        // Make the next move
        makeMove(game, nextMove);

        #ifdef LOGGING
            // Log the game state and opponent's move
            logGameState(game, nextMove);
        #endif

        // Check for a winner
        checkForWinner(game);
        if (game->winner != EMPTY) {
            break;
        }
    } 

    #ifdef LOGGING
        // Print the winner
        if (game->winner == BLACK) {
            logString("BLACK wins!\n");
            printf("BLACK wins!\n");
        } else if (game->winner == WHITE) {
            logString("WHITE wins!\n");
            printf("WHITE wins!\n");
        } else {
            logString("It's a tie!\n");
            printf("It's a tie!\n");
        }
    #endif

    // Free the memory
    free(gameStateString);
    free(nextMoveString);
    free(game);

    return 0;
}
