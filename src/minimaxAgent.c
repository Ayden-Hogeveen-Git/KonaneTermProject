#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "structures.h"
#include "konane.h"


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

int evalCountBW(Node* node) {
	// Initialize the counters
	int blackCount = 0;
	int whiteCount = 0;

	// Loop through the board
	for (int y = 7; y >= 0; y--) {
		for (int x = 0; x <= 7; x++) {
			// If the piece is black, increment the black counter
			if (node->game.board[y][x] == BLACK) {
				blackCount++;
			} else if (node->game.board[y][x] == WHITE) {
				whiteCount++;
			}
		}
	}

	// Return the difference between the two counters
	if (node->game.maxPlayer == BLACK) {
		return (blackCount - whiteCount) * node->depth;
	} else if (node->game.maxPlayer == WHITE) {
		return (whiteCount - blackCount) * node->depth;
	} else {
		fprintf(stderr, "Error: Invalid max player!\n");
		exit(1);
	}
}

int evalCountSiblings(Node* node) {
	// Generate the children up to the max depth
	generateChildren(node);

	// Count the total number of children
	int totalSiblingsAgent = countSiblings(node);

	// Generate a temporary node for the other player
	Node* tempNode = initializeNode();
	
	// Copy the game state
	tempNode->game = node->game;

	// Switch the turn
	togglePlayer(&tempNode->game);

	// Generate the children
	generateChildren(tempNode);

	// Get the number of valid moves for the other player
	int totalSiblingsOpponent = countSiblings(tempNode);

	// Free the memory
	for (int i = 0; i < tempNode->size; i++) {
		free(tempNode->children[i]);
	}
	free(tempNode->children);
	free(tempNode);

	// Return the difference between the two valid move counts
	return (node->game.turn == node->game.maxPlayer) ?
		(totalSiblingsAgent - totalSiblingsOpponent) * node->depth :
		(totalSiblingsOpponent - totalSiblingsAgent) * node->depth;
}

int evalCountChildren(Node* node) {
	// Generate the children up to the max depth
	generateChildren(node);

	// Generate the tree up to the max depth
	generateTree(node, MAX_TREE_DEPTH);

	// Count the total number of children
	int totalChildrenAgent = countChildren(node);

	// Generate a temporary node for the other player
	Node* tempNode = initializeNode();
	
	// Copy the game state
	tempNode->game = node->game;

	// Switch the turn
	togglePlayer(&tempNode->game);

	// Generate the children
	generateChildren(tempNode);

	// Generate the tree up to the max depth
	generateTree(tempNode, MAX_TREE_DEPTH);

	// Get the number of valid moves for the other player
	int totalChildrenOpponent = countChildren(tempNode);

	// Free the memory
	for (int i = 0; i < tempNode->size; i++) {
		free(tempNode->children[i]);
	}
	free(tempNode->children);
	free(tempNode);

	// Return the difference between the two valid move counts
	return (node->game.turn == node->game.maxPlayer) ?
		(totalChildrenAgent - totalChildrenOpponent) * node->depth :
		(totalChildrenOpponent - totalChildrenAgent) * node->depth;
}

int evalCountJumps(Node* node) {
	// Count the total number of jumps that the move can make
	if (node->depth == 0) {
		return node->game.prevMove.jumps * 5;
	} else if (node->depth == 1) {
		return node->game.prevMove.jumps * 3;
	} else if (node->depth == 2) {
		return node->game.prevMove.jumps * 2;
	} else if (node->depth == 3) {
		return node->game.prevMove.jumps;
	} else {
		return 0;
	}
}

int evalAgentWins(GameState* game) {
	// Check for a winner
	checkForWinner(game);

	// If the agent wins, return 1000
	if (game->winner == game->maxPlayer) {
		return 1000;
	} else {
		return 0;
	}
}

int evaluationFunction(Node* node, int type) {
	if (type == 1) {
		return evalCountBW(node);
	} else if (type == 2) {
		return evalCountSiblings(node);
	} else if (type == 3) {
		return evalCountSiblings(node);
	} else if (type == 4) {
		return evalCountJumps(node);
	} else if (type == 5) {
		return evalAgentWins(&node->game);
	} else if (type == 6) {
		return evalCountBW(node) + evalCountChildren(node) + evalCountSiblings(node) +
				evalCountJumps(node) + evalAgentWins(&node->game);
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
	// if (node->size == 0 || depth == 0 || isTerminal(node)) {
	if (node->size == 0 || depth == 0) {
	// if (depth == 0 || isTerminal(node)) {
		return evaluationFunction(node, 6);
	}

	// Recursive Case:
	if (node->game.turn == node->game.maxPlayer) {
		// Initialize bestValue to negative infinity
		int bestValue = INT_MIN;

		// Loop through valid moves
		for (int i = 0; i < node->size; i++) {
			Move tempMove;
			int value = minimax(node->children[i], depth - 1, &tempMove);

			// If value is greater than bestValue, update bestValue
			if (value > bestValue) {
				bestValue = value;
				// Update bestMove
				*bestMove = node->children[i]->game.prevMove;
			}
		}
		return bestValue;

	} else {
		// Initialize bestValue to positive infinity
		int bestValue = INT_MAX;

		// Loop through valid moves
		for (int i = 0; i < node->size; i++) {
			Move tempMove;
			int value = minimax(node->children[i], depth - 1, &tempMove);

			// If value is less than bestValue, update bestValue
			if (value < bestValue) {
				bestValue = value;
				// Update bestMove
				*bestMove = node->children[i]->game.prevMove;
			}
		}
		return bestValue;
	}
}

int minimaxAlphaBeta(Node* node, int depth, int alpha, int beta, Move* bestMove) {
	// Base Case: if depth is 0, or terminal node, compute the utility value of the node
	if (depth == 0 || isTerminal(node)) {
		return evaluationFunction(node, 6);
	}

	// Recursive Case:
	if (node->game.turn == node->game.maxPlayer) {
		// Initialize bestValue to negative infinity
		int bestValue = INT_MIN;

		// Loop through valid moves
		for (int i = 0; i < node->size; i++) {
			Move tempMove;
			int value = minimax(node->children[i], depth - 1, &tempMove);

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
			int value = minimax(node->children[i], depth - 1, &tempMove);

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
