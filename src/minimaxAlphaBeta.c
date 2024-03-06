#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "structures.h"
#include "konane.h"
#include "evaluation.h"


Move chooseFirstMove(GameState* game) {
	// Define all four possible first moves
	Move moveBlack1 = { .start = { .x = 'D', .y = 5 }, .end = { .x = 'D', .y = 5 } };
	Move moveBlack2 = { .start = { .x = 'E', .y = 4 }, .end = { .x = 'E', .y = 4 } };
	Move moveWhite1 = { .start = { .x = 'D', .y = 4 }, .end = { .x = 'D', .y = 4 } };
	Move moveWhite2 = { .start = { .x = 'E', .y = 5 }, .end = { .x = 'E', .y = 5 } };

	// Initialize the random number generator
	srand(time(NULL));

	// If it's the first move for black, return with 50% probability one of the two center pieces
	if (game->turn == BLACK) {
		// Validate both first moves for black
		if (isValidMove(game, game->turn, moveBlack1) && isValidMove(game, game->turn, moveBlack2)) {
			int random = rand() % 2;
			if (random == 0) {
				return moveBlack1;
			} else {
				return moveBlack2;
			}
		} else if (isValidMove(game, game->turn, moveBlack1)) {
			return moveBlack1;
		} else if (isValidMove(game, game->turn, moveBlack2)) {
			return moveBlack2;
		}
	} else if (game->turn == WHITE) {
		// Validate both first moves for white
		if (isValidMove(game, game->turn, moveWhite1) && isValidMove(game, game->turn, moveWhite2)) {
			int random = rand() % 2;
			if (random == 0) {
				return moveWhite1;
			} else {
				return moveWhite2;
			}
		} else if (isValidMove(game, game->turn, moveWhite1)) {
			return moveWhite1;
		} else if (isValidMove(game, game->turn, moveWhite2)) {
			return moveWhite2;
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

int minimaxAlphaBeta(Node* node, int maxSearchDepth, int alpha, int beta, Move* bestMove) {
	// Base Case: if depth is 0, or terminal node, compute the utility value of the node
	if (maxSearchDepth == 0 || isTerminal(node)) {
		return evaluationFunction(node, 6);
	}

	// Recursive Case:
	if (node->game.turn == node->game.maxPlayer) {
		// Initialize bestValue to negative infinity
		int bestValue = INT_MIN;

		// Loop through valid moves
		for (int i = 0; i < node->size; i++) {
			Move tempMove;
			int value = minimaxAlphaBeta(node->children[i], maxSearchDepth - 1, alpha, beta, &tempMove);

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
			Move tempMove;
			int value = minimaxAlphaBeta(node->children[i], maxSearchDepth - 1, alpha, beta, &tempMove);

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