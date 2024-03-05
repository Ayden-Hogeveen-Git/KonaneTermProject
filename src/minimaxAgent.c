#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "structures.h"
#include "konane.h"


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
	for (int y = 8; y > 0; y--) {
		for (int x = 0; x < 8; x++) {
			// If the piece is black, increment the black counter
			if (game->board[y - 1][x] == BLACK) {
				blackCount++;
			} else if (game->board[y - 1][x] == WHITE) {
				whiteCount++;
			}
		}
	}

	// Return the difference between the two counters
	if (game->maxPlayer == BLACK) {
		return blackCount - whiteCount;
	} else if (game->maxPlayer == WHITE) {
		return whiteCount - blackCount;
	} else {
		fprintf(stderr, "Error: Invalid max player!\n");
		exit(1);
	}
}

int countChildren(Node* node) {
	// Initialize the counter
	int count = 0;

	// Loop through the node's children
	for (int i = 0; i < node->size; i++) {
		// Increment the counter
		count += countChildren(node->children[i]);
	}

	// Return the counter
	return count;
}

int evalCalcMobility(Node* node) {
	// Generate the children up to the max depth
	generateChildren(node);

	// Count the total number of children
	int currentValidMoves = countChildren(node);

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
	int opponentValidMoves = tempNode->size;

	// Free the memory
	for (int i = 0; i < tempNode->size; i++) {
		free(tempNode->children[i]);
	}
	free(tempNode->children);
	free(tempNode);

	// Return the difference between the two valid move counts
	return (node->game.turn == node->game.maxPlayer) ?
		currentValidMoves - opponentValidMoves : opponentValidMoves - currentValidMoves;
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

int minimax(Node* node, int depth, Move* bestMove) {
	// Check if it's the first move for black or white
	if (node->game.firstMove && isFirstMove(&node->game)) {
		// Return the first move
		*bestMove = chooseFirstMove(&node->game);
		return 0;
	}

	// Base Case: if depth is 0, or terminal node, compute the utility value of the node
	if (depth == 0 || isTerminal(node)) {
		// node->value = evaluationFunction(node, 3);
		return evaluationFunction(node, 3);
	}

	// // Initialize a temporary move
	// Move tempMove;

	// Recursive Case:
	if (node->game.turn == node->game.maxPlayer) {
		// Initialize bestValue to negative infinity
		int bestValue = INT_MIN;

		// Loop through valid moves
		for (int i = 0; i < node->size; i++) {
			Move tempMove = node->children[i]->game.prevMove;
			int value = minimax(node->children[i], depth - 1, bestMove);
			// int value = minimax(node->children[i], depth - 1, &tempMove);

			// If value is greater than bestValue, update bestValue
			if (value > bestValue) {
				bestValue = value;
				// Update bestMove
				// *bestMove = node->children[i]->game.prevMove;
				*bestMove = tempMove;
			}
		}
		return bestValue;

	} else {
		// Initialize bestValue to positive infinity
		int bestValue = INT_MAX;

		// Loop through valid moves
		for (int i = 0; i < node->size; i++) {
			Move tempMove = node->children[i]->game.prevMove;
			int value = minimax(node->children[i], depth - 1, bestMove);
			// int value = minimax(node->children[i], depth - 1, &tempMove);

			// If value is less than bestValue, update bestValue
			if (value < bestValue) {
				bestValue = value;
				// Update bestMove
				// *bestMove = node->children[i]->game.prevMove;
				*bestMove = tempMove;
			}
		}
		return bestValue;
	}
}

int minimaxAlphaBeta(Node* node, int depth, int alpha, int beta, Move* bestMove) {
	// Base Case: if depth is 0, or terminal node, compute the utility value of the node
	if (depth == 0 || isTerminal(node)) {
		// node->value = evaluationFunction(node, 3);
		return evaluationFunction(node, 3);
	}

	// Recursive Case:
	if (node->game.turn == node->game.maxPlayer) {
		// Initialize bestValue to negative infinity
		int bestValue = INT_MIN;

		// Loop through valid moves
		for (int i = 0; i < node->size; i++) {
			int value = minimax(node->children[i], depth - 1, bestMove);

			// If value is greater than bestValue, update bestValue
			if (value > bestValue) {
				bestValue = value;
				// Update bestMove
				*bestMove = node->children[i]->game.prevMove;
			}

			// Perform alpha-beta pruning
			alpha = max(alpha, bestValue);
			if (beta <= alpha) {
				break;
			}
		}
		return bestValue;

	} else {
		// Initialize bestValue to positive infinity
		int bestValue = INT_MAX;

		// Loop through valid moves
		for (int i = 0; i < node->size; i++) {
			int value = minimax(node->children[i], depth - 1, bestMove);

			// If value is less than bestValue, update bestValue
			if (value < bestValue) {
				bestValue = value;
				// Update bestMove
				*bestMove = node->children[i]->game.prevMove;
			}

			// Perform alpha-beta pruning
			beta = min(beta, bestValue);
			if (beta <= alpha) {
				break;
			}
		}
		return bestValue;
	}
}
