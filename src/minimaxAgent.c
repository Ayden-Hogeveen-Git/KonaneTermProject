#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "konane.h"


// Function prototypes
int minValue(Board* board, ValidMoves validMoves, int depth, int alpha, int beta);
int maxValue(Board* board, ValidMoves validMoves, int depth, int alpha, int beta);


int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int minValue(Board* board, ValidMoves validMoves, int depth, int alpha, int beta) {
    /*
    function MIN-VALUE(state) returns a utility value
     if TERMINAL-TEST(state) then return UTILITY(state)
     v ← ∞
     for a,s in SUCCESSORS(state) do
     v ← MIN(v,MAX-VALUE(s))
     return v
    */

    // If terminal state, return utility value of 0
    if (validMoves.size == 0 || depth == 0) {
        return 0;
    }

    // Initialize v to positive infinity
    int v = 1000;

    // Loop through valid moves
    for (int i = 0; i < validMoves.size; i++) {
        // Copy the board
        Board* nextState = copyBoard(board);

        // Make the move on the copy
        makeMove(nextState, validMoves.moves[i]);

		// Calculate the valid moves for the next state
		ValidMoves nextValidMoves = findValidMoves(nextState);

        // Get the max value
        v = min(v, maxValue(nextState, nextValidMoves, depth - 1, alpha, beta));

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

int maxValue(Board* board, ValidMoves validMoves, int depth, int alpha, int beta) {
    /*
    function MAX-VALUE(state) returns a utility value
     if TERMINAL-TEST(state) then return UTILITY(state)
     v ← - ∞
     for a,s in SUCCESSORS(state) do
     v ← MAX(v,MIN-VALUE(s))
     return v
     */

    // If terminal state, return utility value
    if (validMoves.size == 0 || depth == 0) {
        return 0;
    }

    // Initialize v to negative infinity
    int v = -1000;

    // Loop through valid moves
    for (int i = 0; i < validMoves.size; i++) {
        // Copy the board
        Board* nextState = copyBoard(board);

        // Make the move on the copy
        makeMove(nextState, validMoves.moves[i]);

		// Calculate the valid moves for the next state
		ValidMoves nextValidMoves = findValidMoves(nextState);

        // Get the min value
        v = max(v, minValue(nextState, nextValidMoves, depth - 1, alpha, beta));
	
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
Move minimax(Board* board) {
    /*
    function MINIMAX-DECISION(state) returns an action
     inputs: state, current state in game
     v←MAX-VALUE(state)
     return the action in SUCCESSORS(state) with value v
    */

    // Find valid moves
    ValidMoves validMoves = findValidMoves(board);

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
        Board* nextState = copyBoard(board);

        // Make the move on the copy
        makeMove(nextState, validMoves.moves[i]);

		// Calculate the valid moves for the next state
		ValidMoves nextValidMoves = findValidMoves(nextState);

        // Get the value of the next state
        int value;

        // If player is maximizing, get the max value
        if (board->player == MAXIMIZING_PLAYER) {
            // Get the max value
            value = maxValue(nextState, nextValidMoves, MAX_DEPTH, alpha, beta);
            
            // If value is greater than max, update max
            if (value > alpha) {
                alpha = value;
                bestMoveIndex = i;
            }
        } else if (board->player == MINIMIZING_PLAYER) {
            // Get the min value
            value = minValue(nextState, nextValidMoves, MAX_DEPTH, alpha, beta);

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
