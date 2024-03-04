#include <stdlib.h>
#include <stdio.h>
#include <time.h>	
#include "structures.h"
#include "konane.h"


// Function prototypes
int minValue(Node* node, int depth);
int maxValue(Node* node, int depth);

int minValueAlphaBeta(Node* node, int depth, int alpha, int beta);
int maxValueAlphaBeta(Node* node, int depth, int alpha, int beta);


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

// int calculateMobility(GameState* game, Player player) {
//     int mobility = 0;
//     char playerSymbol = player ? BLACK : WHITE;

//     // Loop through the board
// 	for (int j = 8; j > 0; j--) {
// 		for (int i = 0; i < 8; i++) {
// 			// Counts the valid moves of the player
//             if (game->board[j][i] == playerSymbol) {
//                 ValidMoves validMoves = findValidMoves(game);
//                 mobility += validMoves.size;
//                 freeValidMoves(&validMoves);
//             }
//         }
//     }

//     return mobility;
// }

// int evaluateGameState(GameState* game) {
//     int mobilityMax = calculateMobility(game, game->maxPlayer);
//     int mobilityMin = calculateMobility(game, game->minPlayer);

//     // Other evaluation factors?

//     // Combine the evaluation factors into an overall evaluation score
//     int evaluation = mobilityMax - mobilityMin;

//     return evaluation;
// }

int evalCalcMobility(Node* node) {
	// Get the number of valid moves for the current player
	int currentValidMoves = node->size;

	// Generate a temporary node for the other player
	Node* tempNode = malloc(sizeof(Node));

	//	Check if memory was allocated
	if (tempNode == NULL) {
		fprintf(stderr, "Error: Memory not allocated for tempNode\n");
		exit(1);
	}

	// Initialize the temporary node
	tempNode->game = node->game;
	tempNode->capacity = 10;
	tempNode->size = 0;

	// Allocate memory for the children array
	tempNode->children = malloc(tempNode->capacity * sizeof(Node*));

	// Check if memory was allocated
	if (tempNode->children == NULL) {
		fprintf(stderr, "Error: Memory not allocated for children\n");
		exit(1);
	}

	// Switch the turn
	togglePlayer(&tempNode->game);

	// Generate the children
	generateChildren(tempNode);

	// Get the number of valid moves for the other player
	int otherValidMoves = tempNode->size;

	// Free the memory
	for (int i = 0; i < tempNode->size; i++) {
		free(tempNode->children[i]);
	}
	free(tempNode);

	// Return the difference between the two valid move counts
	// return currentValidMoves - otherValidMoves;
	return (node->game.turn == node->game.maxPlayer) ?
		currentValidMoves - otherValidMoves : otherValidMoves - currentValidMoves;
}

int evaluationFunction(Node* node, int type) {
	if (type == 1) {
		return evalCountBW(&node->game);
	} else if (type == 2) {
		return evalCalcMobility(node);
	} else if (type == 3) {
		return evalCountBW(&node->game) + evalCalcMobility(node);
	} else {
		fprintf(stderr, "Error: Invalid evaluation function type!\n");
		exit(1);
	}
}

int minValue(Node* node, int depth) {
	// If terminal game, or depth is 0, return utility value
	if (node->size == 0 || depth <= 0) {
		return evaluationFunction(node, 1);
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
	// If terminal game, or depth is 0, return utility value
	if (node->size == 0 || depth <= 0) {
		return evaluationFunction(node, 1);
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

int minValueAlphaBeta(Node* node, int depth, int alpha, int beta) {
	// If terminal state, or depth is 0, return utility value
	if (node->size == 0 || depth == 0) {
		return evaluationFunction(node, 3);
    }

	// Initialize v to positive infinity
	int v = 1000;

	// Loop through valid moves
	for (int i = 0; i < node->size; i++) {
		// Get the max value
		v = min(v, maxValueAlphaBeta(node->children[i], depth - 1, alpha, beta));

	// Perform Alpha-Beta Pruning
	if (v <= alpha) {
		return v;
	}
	beta = min(beta, v);
	}

	// Return v
	return v;
}

int maxValueAlphaBeta(Node* node, int depth, int alpha, int beta) {
	// If terminal state, or depth is 0, return utility value
	if (node->size == 0 || depth == 0) {
		return evaluationFunction(node, 3);
	}

	// Initialize v to negative infinity
	int v = -1000;

	// Loop through valid moves
	for (int i = 0; i < node->size; i++) {
		// Get the min value
		v = max(v, minValueAlphaBeta(node->children[i], depth - 1, alpha, beta));

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
	// Determine if it's the first move for black or white
	if (game->firstMove && isFirstMove(game)) {
		// If it's the first move, return the first chosen move
		return chooseFirstMove(game);
	}

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

	// Allocate memory for the children array
	node->children = malloc(node->capacity * sizeof(Node*));

	// Check if memory was allocated
	if (node->children == NULL) {
		fprintf(stderr, "Error: Memory not allocated for children\n");
		exit(1);
	}

	// Generate the children
	generateChildren(node);

	// If there are no valid moves, determine the winner
	if (node->size == 0) {
		// If the current player is black, the winner is white
		if (game->turn == BLACK) {
			game->winner = WHITE;
			return (Move) { .start = { .x = 'A', .y = -1 }, .end = { .x = 'A', .y = -1 } };
		} else if (game->turn == WHITE) {
			// If the current player is white, the winner is black
			game->winner = BLACK;
			return (Move) { .start = { .x = 'A', .y = -1 }, .end = { .x = 'A', .y = -1 } };
		}
	}

	// Initialize best move index
	int bestMoveIndex = -1;

	// Initialize max and min values
	// Max wants to maximize the total number of valid moves
	// Min wants to minimize the total number of valid moves
	int max = -1000; // Max is initialized to negative infinity
	int min = 1000; // Min is initialized to positive infinity

	// Loop through valid moves
	for (int i = 0; i < node->size; i++) {
		// If player is maximizing, get the max value
		if (node->game.turn == node->game.maxPlayer) {
			// Get the max value
			int value = maxValue(node->children[i], MAX_DEPTH);

			// If value is greater than max, update max
			if (value > max) {
				max = value;
				bestMoveIndex = i;
			}
		} else if (node->game.turn == node->game.minPlayer) {
			// Get the min value
			int value = minValue(node->children[i], MAX_DEPTH);

			// If value is less than min, update min
			if (value < min) {
				min = value;
				bestMoveIndex = i;
			}
		}
	}

	// Check if the best move index is still -1
	if (bestMoveIndex == -1) {
		fprintf(stderr, "Warning: No best move found!\n");
		exit(1);
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
	// Determine if it's the first move for black or white
	if (game->firstMove && isFirstMove(game)) {
		// If it's the first move, return the first chosen move
		return chooseFirstMove(game);
	}

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

	// Allocate memory for the children array
	node->children = malloc(node->capacity * sizeof(Node*));

	// Check if memory was allocated
	if (node->children == NULL) {
		fprintf(stderr, "Error: Memory not allocated for children\n");
		exit(1);
	}

	// Generate the children
	generateChildren(node);

	// If there are no valid moves, determine the winner
	if (node->size == 0) {
		// If the current player is black, the winner is white
		if (game->turn == BLACK) {
			game->winner = WHITE;
			return (Move) { .start = { .x = 'A', .y = -1 }, .end = { .x = 'A', .y = -1 } };
		} else if (game->turn == WHITE) {
			// If the current player is white, the winner is black
			game->winner = BLACK;
			return (Move) { .start = { .x = 'A', .y = -1 }, .end = { .x = 'A', .y = -1 } };
		}
	}

	// Initialize best move index
	int bestMoveIndex = -1;

	// Initialize Alpha and Beta
	int alpha = -1000;
	int beta = 1000;

	// Loop through valid moves
	for (int i = 0; i < node->size; i++) {
		// Get the value of the next game
		int value;

		// If player is maximizing, get the max value
		if (node->game.turn == node->game.maxPlayer) {
			// Get the max value
			value = maxValueAlphaBeta(node->children[i], MAX_DEPTH, alpha, beta);

			// If value is greater than alpha, update alpha
			if (value > alpha) {
				alpha = value;
				bestMoveIndex = i;
			}
		} else if (node->game.turn == node->game.minPlayer) {
			// Get the min value
			value = minValueAlphaBeta(node->children[i], MAX_DEPTH, alpha, beta);

			// If value is less than beta, update beta
			if (value < beta) {
				beta = value;
				bestMoveIndex = i;
			}
		}
	}

	// Check if the best move index is still -1
	if (bestMoveIndex == -1) {
		fprintf(stderr, "Warning: No best move found!\n");
		exit(1);
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
