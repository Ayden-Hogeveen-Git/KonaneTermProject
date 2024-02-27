#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "konane.h"


// Function prototypes
int minValue(Node* node, int depth);
int maxValue(Node* node, int depth);
// int minValue(GameState* game, int depth);
// int maxValue(GameState* game, int depth);

//int minValue(GameState* game, ValidMoves validMoves, int alpha, int beta)
//int maxValue(GameState* game, ValidMoves validMoves, int alpha, int beta)


int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
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

	// Generate all the valid moves as children
	generateChildren(node);

	// If terminal game, return utility value of 0
	if (node->size == 0) {
		return 0;
	}

	// If depth is 0, return heuristic utility value
	if (depth == 0) {
		return &node->size;
	}

	// Initialize v to positive infinity
	int v = 1000;

	// Loop through valid moves
	for (int i = 0; i < node->size; i++) {
		// Get the max value
		v = min(v, maxValue(&node->children[i], depth - 1));
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

	// Generate all the valid moves as children
	generateChildren(node);

	// If terminal game, return utility value
	if (node->size == 0) {
		return 0;
	}

	// If depth is 0, return heuristic utility value
	if (depth == 0) {
		return &node->size;
	}

	// Initialize v to negative infinity
	int v = -1000;

	// Loop through valid moves
	for (int i = 0; i < node->size; i++) {
		// Get the min value
		v = max(v, minValue(&node->children[i], depth - 1));
	}

	// Return v
	return v;
}

// int minValue(GameState* game, int depth) {
//     /*
//     function MIN-VALUE(game) returns a utility value
//      if TERMINAL-TEST(game) then return UTILITY(game)
//      v ← ∞
//      for a,s in SUCCESSORS(game) do
//      v ← MIN(v,MAX-VALUE(s))
//      return v
//     */

//     // If terminal game, return utility value of 0
//     if (validMoves.size == 0 || depth == 0) {
//         return 0;
//     }

//     // Initialize v to positive infinity
//     int v = 1000;

//     // Loop through valid moves
//     for (int i = 0; i < validMoves.size; i++) {
//         // Copy the game
//         GameState* nextState = copyBoard(game);

//         // Make the move on the copy
//         makeMove(nextState, validMoves.moves[i]);

// 		// Calculate the valid moves for the next game
// 		ValidMoves nextValidMoves = findValidMoves(nextState);

//         // Get the max value
//         v = min(v, maxValue(nextState, nextValidMoves, depth - 1));

//         // Free the memory
//         free(nextState);
// 		free(nextValidMoves.moves);
//     }

//     // Return v
//     return v;
// }

// int maxValue(GameState* game, int depth) {
//     /*
//     function MAX-VALUE(game) returns a utility value
//      if TERMINAL-TEST(game) then return UTILITY(game)
//      v ← - ∞
//      for a,s in SUCCESSORS(game) do
//      v ← MAX(v,MIN-VALUE(s))
//      return v
//      */

//     // If terminal game, return utility value
//     if (validMoves.size == 0 || depth == 0) {
//         return 0;
//     }

//     // Initialize v to negative infinity
//     int v = -1000;

//     // Loop through valid moves
//     for (int i = 0; i < validMoves.size; i++) {
//         // Copy the game
//         GameState* nextState = copyBoard(game);

//         // Make the move on the copy
//         makeMove(nextState, validMoves.moves[i]);

// 		// Calculate the valid moves for the next game
// 		ValidMoves nextValidMoves = findValidMoves(nextState);

//         // Get the min value
//         v = max(v, minValue(nextState, nextValidMoves, depth - 1));
	
// 		// Free the memory
// 		free(nextState);
// 		free(nextValidMoves.moves);
//     }


//     // Return v
//     return v;
// }

/*Alpha-Beta for minValue*/
/*
int minValue(GameState* game, int playersTurn, ValidMoves validMoves, int alpha, int beta) {

    // If terminal game, return utility value of 0
    if (findValidMoves(game, playersTurn).size == 0) {
        return 0;
    }

    // Loop through valid moves
    for (int i = 0; i < validMoves.size; i++) {
        // Get the next game
        GameState* nextState = minMaxResult(game, validMoves.moves[i]);

        // Get the max value
        int v = maxValue(nextState, findValidMoves(nextState), alpha, beta);

        // Update beta
        beta = min(beta, v);

        // Perform pruning
        if (beta <= alpha) {
            return beta;
        }
    }
    return beta;
}
*/
/*Alpha-Beta for maxValue*/
/*
int maxValue(GameState* game, int playersTurn, ValidMoves validMoves, int alpha, int beta) {

    // If terminal game, return utility value of 0
    if (findValidMoves(game, playersTurn).size == 0) {
        return 0;
    }

    // Loop through valid moves
    for (int i = 0; i < validMoves.size; i++) {
        // Get the next game
        GameState* nextState = minMaxResult(game, validMoves.moves[i]);

        // Get the min value
        int v = minValue(nextState, findValidMoves(nextState), alpha, beta);

        // Update alpha
        alpha = max(alpha, v);

        // Perform pruning
        if (alpha >= beta) {
            return alpha;
        }
    }
    return alpha;
}
*/

Move minimax(GameState* game) {
    /*
    function MINIMAX-DECISION(game) returns an action
     inputs: game, current game in game
     v←MAX-VALUE(game)
     return the action in SUCCESSORS(game) with value v
    */

    // Initialize the root node
	Node* node = malloc(sizeof(Node));
	node->game = *game;
	node->capacity = 10;
	node->size = 0;

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
		if (node->game.player == MAXIMIZING_PLAYER) {
			// Get the max value
			value = maxValue(&node->children[i], MAX_DEPTH);

			// If value is greater than max, update max
			if (value > max) {
				max = value;
				bestMoveIndex = i;
			}
		} else if (node->game.player == MINIMIZING_PLAYER) {
			// Get the min value
			value = minValue(&node->children[i], MAX_DEPTH);

			// If value is less than min, update min
			if (value < min) {
				min = value;
				bestMoveIndex = i;
			}
		}
	}

	// Store the best move
	Move bestMove = node->children[bestMoveIndex].game.prevMove;

	// Free the memory
	free(node);
	// for (int i = 0; i < node->size; i++) {
	// 	free(node->children[i].game.game);
	// }

	// Return best move
	return bestMove;
}

// Move minimax(GameState* game) {
//     /*
//     function MINIMAX-DECISION(game) returns an action
//      inputs: game, current game in game
//      v←MAX-VALUE(game)
//      return the action in SUCCESSORS(game) with value v
//     */

//     // Find valid moves
//     ValidMoves validMoves = findValidMoves(game);

//     // Initialize best move index
//     int bestMoveIndex = -1;

//     // Initialize max and min values
//     // Max wants to maximize the total number of valid moves
//     // Min wants to minimize the total number of valid moves
//     int max = -1000; // Max is initialized to negative infinity
//     int min = 1000; // Min is initialized to positive infinity

//     // Loop through valid moves
//     for (int i = 0; i < validMoves.size; i++) {
//         // Copy the game
//         GameState* nextState = copyBoard(game);

//         // Make the move on the copy
//         makeMove(nextState, validMoves.moves[i]);

// 		// Calculate the valid moves for the next game
// 		ValidMoves nextValidMoves = findValidMoves(nextState);

//         // Get the value of the next game
//         int value;

//         // If player is maximizing, get the max value
//         if (game->player == MAXIMIZING_PLAYER) {
//             // Get the max value
//             value = maxValue(nextState, nextValidMoves, MAX_DEPTH);
            
//             // If value is greater than max, update max
//             if (value > max) {
//                 max = value;
//                 bestMoveIndex = i;
//             }
//         } else if (game->player == MINIMIZING_PLAYER) {
//             // Get the min value
//             value = minValue(nextState, nextValidMoves, MAX_DEPTH);

//             // If value is less than min, update min
//             if (value < min) {
//                 min = value;
//                 bestMoveIndex = i;
//             }
//         }

//         // Free the memory
//         free(nextState);
// 		free(nextValidMoves.moves);
// 	}

// 	// Store the best move
// 	Move bestMove = validMoves.moves[bestMoveIndex];

// 	// Free the memory
// 	freeValidMoves(&validMoves);

//     // Return best move
//     return bestMove;
// }
