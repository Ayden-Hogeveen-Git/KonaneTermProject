#include <stdlib.h>
#include <stdio.h>
#include <time.h>	
#include "structures.h"
#include "konane.h"


// Function prototypes
int minValue(Node* node, int depth);
int maxValue(Node* node, int depth);

int minValueAlphaBeta(GameState* game, ValidMoves validMoves, int depth, int alpha, int beta);
int maxValueAlphaBeta(GameState* game, ValidMoves validMoves, int depth, int alpha, int beta);
// int minValueAlphaBeta(Node* node, ValidMoves validMoves, int depth, int alpha, int beta);
// int maxValueAlphaBeta(Node* node, ValidMoves validMoves, int depth, int alpha, int beta);


Move chooseFirstMove(GameState* game) {
	// Define all four possible first moves
	Move moveBlack1 = { .start = { .x = 'D', .y = 5 }, .end = { .x = 'D', .y = 5 } };
	Move moveBlack2 = { .start = { .x = 'E', .y = 4 }, .end = { .x = 'E', .y = 4 } };
	Move moveWhite1 = { .start = { .x = 'D', .y = 4 }, .end = { .x = 'D', .y = 4 } };
	Move moveWhite2 = { .start = { .x = 'E', .y = 5 }, .end = { .x = 'E', .y = 5 } };

	// Seed the random number generator using the current time
	srand(time(NULL));

	// If it's the first move for black, return with 50% probability one of the two center pieces
	if (game->turn == BLACK) {
		// Validate both first moves for black
		if (isValidFirstMove(game, moveBlack1.start) && isValidFirstMove(game, moveBlack2.start)) {
			int random = rand() % 2;
			if (random == 0) {
				return moveBlack1;
			} else {
				return moveBlack2;
			}
		}
	} else if (game->turn == WHITE) {
		// Validate both first moves for white
		if (isValidFirstMove(game, moveWhite1.start) && isValidFirstMove(game, moveWhite2.start)) {
			int random = rand() % 2;
			if (random == 0) {
				return moveWhite1;
			} else {
				return moveWhite2;
			}
		}
	}
	
	// Default move
	return moveBlack1;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int evalCountBW(GameState* game) {
	// Initialize the counters
	int blackCount = 0;
	int whiteCount = 0;

	// Loop through the board
	for (int j = 8; j > 0; j--) {
		for (int i = 0; i < 8; i++) {
			// If the piece is black, increment the black counter
			if (game->board[j - 1][i] == BLACK) {
				blackCount++;
			} else if (game->board[j - 1][i] == WHITE) {
				whiteCount++;
			}
		}
	}

	// Return the difference between the two counters
	if (game->turn == BLACK) {
		return blackCount - whiteCount;
	} else {
		return whiteCount - blackCount;
	}
}

int minValue(Node* node, int depth) {
	/*
	function MIN-VALUE(game) returns a utility value
	 if TERMINAL-TEST(game) then return UTILITY(game)
	 v ← ∞
	 for a,s in SUCCESSORS(game) do
	 v ← MIN(v,MAX-VALUE(s))
	 return v
	*/

	// If terminal game, or depth is 0, return utility value
	if (node->size == 0 || depth <= 0) {
		return evalCountBW(&node->game);
	}

	// Initialize v to positive infinity
	int v = 1000;

	// Loop through valid moves
	for (int i = 0; i < node->size; i++) {
		// Get the max value
		v = min(v, maxValue(node->children[i], depth - 1));
	}

	// Return v
	return v;
}

int maxValue(Node* node, int depth) {
	/*
	function MAX-VALUE(game) returns a utility value
	 if TERMINAL-TEST(game) then return UTILITY(game)
	 v ← - ∞
	 for a,s in SUCCESSORS(game) do
	 v ← MAX(v,MIN-VALUE(s))
	 return v
	*/

	// If terminal game, or depth is 0, return utility value
	if (node->size == 0 || depth <= 0) {
		return evalCountBW(&node->game);
	}

	// Initialize v to negative infinity
	int v = -1000;

	// Loop through valid moves
	for (int i = 0; i < node->size; i++) {
		// Get the min value
		v = max(v, minValue(node->children[i], depth - 1));
	}

	// Return v
	return v;
}

int minValueAlphaBeta(GameState* game, ValidMoves validMoves, int depth, int alpha, int beta) {
    /*
    function MIN-VALUE(state) returns a utility value
     if TERMINAL-TEST(state) then return UTILITY(state)
     v ← ∞
     for a,s in SUCCESSORS(state) do
     v ← MIN(v,MAX-VALUE(s))
     return v
    */

    // If terminal state, or depth is 0, return utility value
    if (validMoves.size == 0 || depth == 0) {
        return evalCountBW(game);
    }

    // Initialize v to positive infinity
    int v = 1000;

    // Loop through valid moves
    for (int i = 0; i < validMoves.size; i++) {
        // Copy the board
        GameState* nextState = copyGameState(*game);

        // Make the move on the copy
        makeMove(nextState, validMoves.moves[i]);

		// Calculate the valid moves for the next state
		ValidMoves nextValidMoves = findValidMoves(nextState);

        // Get the max value
        v = min(v, maxValueAlphaBeta(nextState, nextValidMoves, depth - 1, alpha, beta));

        // Free the memory
        free(nextState);
		free(nextValidMoves.moves);

	// Perform Alpha-Beta Pruning
	if (v <= alpha) {
		return v;
	}
	beta = min(beta, v);
    }

    // Return v
    return v;
}

int maxValueAlphaBeta(GameState* game, ValidMoves validMoves, int depth, int alpha, int beta) {
    /*
    function MAX-VALUE(state) returns a utility value
     if TERMINAL-TEST(state) then return UTILITY(state)
     v ← - ∞
     for a,s in SUCCESSORS(state) do
     v ← MAX(v,MIN-VALUE(s))
     return v
     */

    // If terminal state, or depth is 0, return utility value
    if (validMoves.size == 0 || depth == 0) {
        return evalCountBW(game);
    }

    // Initialize v to negative infinity
    int v = -1000;

    // Loop through valid moves
    for (int i = 0; i < validMoves.size; i++) {
        // Copy the board
        GameState* nextState = copyGameState(*game);

        // Make the move on the copy
        makeMove(nextState, validMoves.moves[i]);

		// Calculate the valid moves for the next state
		ValidMoves nextValidMoves = findValidMoves(nextState);

        // Get the min value
        v = max(v, minValueAlphaBeta(nextState, nextValidMoves, depth - 1, alpha, beta));
	
		// Free the memory
		free(nextState);
		free(nextValidMoves.moves);

	// Perform Alpha-Beta Pruning
	if (v >= beta) {
		return v;
	}
	alpha = max(alpha, v);
    }


    // Return v
    return v;
}

Move minimax(GameState* game) {
    /*
    function MINIMAX-DECISION(game) returns an action
     inputs: game, current game in game
     v←MAX-VALUE(game)
     return the action in SUCCESSORS(game) with value v
    */
    
	// Determine if it's the first move for black or white
	if (game->firstMove && isFirstMove(game)) {
		// If it's the first move, return the first chosen move
		return chooseFirstMove(game);
	}

    // Allocate memory for the root node
	Node* node = malloc(sizeof(Node));

	// Check if memory was allocated
	if (node == NULL) {
		printf("Error: Memory not allocated for node\n");
		exit(1);
	}

	// Initialize the node
	node->game = *game;
	node->capacity = 10;
	node->size = 0;

	// Allocate memory for the children array
	node->children = malloc(node->capacity * sizeof(Node*));

	// Check if memory was allocated
	if (node->children == NULL) {
		printf("Error: Memory not allocated for children\n");
		exit(1);
	}

	// Generate the children
	generateChildren(node);

	// Initialize best move index
	int bestMoveIndex = -1;

	// Initialize max and min values
	// Max wants to maximize the total number of valid moves
	// Min wants to minimize the total number of valid moves
	int max = -1000; // Max is initialized to negative infinity
	int min = 1000; // Min is initialized to positive infinity

	// Loop through valid moves
	for (int i = 0; i < node->size; i++) {
		// Get the value of the next game
		int value;

		// If player is maximizing, get the max value
		if (node->game.turn == node->game.maxPlayer) {
			// Get the max value
			value = maxValue(node->children[i], MAX_DEPTH);

			// If value is greater than max, update max
			if (value > max) {
				max = value;
				bestMoveIndex = i;
			}
		} else if (node->game.turn == node->game.minPlayer) {
			// Get the min value
			value = minValue(node->children[i], MAX_DEPTH);

			// If value is less than min, update min
			if (value < min) {
				min = value;
				bestMoveIndex = i;
			}
		}
	}

	// Store the best move
	Move bestMove = node->children[bestMoveIndex]->game.prevMove;

	// Free the memory
	for (int i = 0; i < node->size; i++) {
		free(node->children[i]);
	}
	free(node);

	// Return best move
	return bestMove;
}

Move minimaxAlphaBeta(GameState* game) {
	/*
    function MINIMAX-DECISION(state) returns an action
     inputs: state, current state in game
     v←MAX-VALUE(state)
     return the action in SUCCESSORS(state) with value v
    */
    
	// Determine if it's the first move for black or white
	if (game->firstMove && isFirstMove(game)) {
		// If it's the first move, return the first chosen move
		return chooseFirstMove(game);
	}

    // Find valid moves
    ValidMoves validMoves = findValidMoves(game);

    // Initialize best move index
    int bestMoveIndex = -1;

    // Initialize Alpha and Beta
    int alpha = -1000;
    int beta = 1000;
	
    // Initialize max and min values
    // Max wants to maximize the total number of valid moves
    // Min wants to minimize the total number of valid moves
    //int max = -1000; // Max is initialized to negative infinity
    //int min = 1000; // Min is initialized to positive infinity

    // Loop through valid moves
    for (int i = 0; i < validMoves.size; i++) {
        // Copy the board
        GameState* nextState = copyGameState(*game);

        // Make the move on the copy
        makeMove(nextState, validMoves.moves[i]);

		// Calculate the valid moves for the next state
		ValidMoves nextValidMoves = findValidMoves(nextState);

        // Get the value of the next state
        int value;

        // If player is maximizing, get the max value
        if (game->turn == game->maxPlayer) {
            // Get the max value
            value = maxValueAlphaBeta(nextState, nextValidMoves, MAX_DEPTH, alpha, beta);
            
            // If value is greater than max, update max
            if (value > alpha) {
                alpha = value;
                bestMoveIndex = i;
            }
        } else if (game->turn == game->minPlayer) {
            // Get the min value
            value = minValueAlphaBeta(nextState, nextValidMoves, MAX_DEPTH, alpha, beta);

            // If value is less than min, update min
            if (value < beta) {
                beta = value;
                bestMoveIndex = i;
            }
        }

        // Free the memory
        free(nextState);
		free(nextValidMoves.moves);
	}

	// Store the best move
	Move bestMove = validMoves.moves[bestMoveIndex];

	// Free the memory
	freeValidMoves(&validMoves);

    // Return best move
    return bestMove;
}
