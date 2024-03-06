#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "konane.h"


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
		return evalCountChildren(node);
	} else if (type == 4) {
		return evalCountJumps(node);
	} else if (type == 5) {
		return evalAgentWins(&node->game);
	} else if (type == 6) {
		return evalCountBW(node) + evalCountSiblings(node) + evalCountChildren(node) + 
				evalCountJumps(node) + evalAgentWins(&node->game);
	} else {
		fprintf(stderr, "Error: Invalid evaluation function type!\n");
		exit(1);
	}
}
