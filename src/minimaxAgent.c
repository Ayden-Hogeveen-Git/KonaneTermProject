#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "konane.h"


// Function prototypes
int minValue(Board* board, ValidMoves validMoves);
int maxValue(Board* board, ValidMoves validMoves);

//int minValue(Board* board, ValidMoves validMoves, int alpha, int beta)
//int maxValue(Board* board, ValidMoves validMoves, int alpha, int beta)


int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int minValue(Board* board, ValidMoves validMoves) {
    /*
    function MIN-VALUE(state) returns a utility value
     if TERMINAL-TEST(state) then return UTILITY(state)
     v ← ∞
     for a,s in SUCCESSORS(state) do
     v ← MIN(v,MAX-VALUE(s))
     return v
    */

    // If terminal state, return utility value of 0
    if (findValidMoves(board).size == 0) {
        return 0;
    }

    // Initialize v to positive infinity
    int v = 1000;

    // Loop through valid moves
    for (int i=0; i<validMoves.size; i++) {
        // Copy the board
        Board* nextState = copyBoard(board);

        // Make the move on the copy
        makeMove(nextState, validMoves.moves[i]);

        // Get the max value
        v = min(v, maxValue(nextState, findValidMoves(nextState)));

        // Free the memory
        free(nextState);
    }

    // Return v
    return v;
}

int maxValue(Board* board, ValidMoves validMoves) {
    /*
    function MAX-VALUE(state) returns a utility value
     if TERMINAL-TEST(state) then return UTILITY(state)
     v ← - ∞
     for a,s in SUCCESSORS(state) do
     v ← MAX(v,MIN-VALUE(s))
     return v
     */

    // If terminal state, return utility value
    if (findValidMoves(board).size == 0) {
        return 0;
    }

    // Initialize v to negative infinity
    int v = -1000;

    // Loop through valid moves
    for (int i=0; i<validMoves.size; i++) {
        // Copy the board
        Board* nextState = copyBoard(board);

        // Make the move on the copy
        makeMove(nextState, validMoves.moves[i]);

        // Get the min value
        v = max(v, minValue(nextState, findValidMoves(nextState)));
    }

    // Return v
    return v;
}

/*Alpha-Beta for minValue*/
/*
int minValue(Board* board, int playersTurn, ValidMoves validMoves, int alpha, int beta) {

    // If terminal state, return utility value of 0
    if (findValidMoves(board, playersTurn).size == 0) {
        return 0;
    }

    // Loop through valid moves
    for (int i = 0; i < validMoves.size; i++) {
        // Get the next state
        Board* nextState = minMaxResult(board, validMoves.moves[i]);

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
int maxValue(Board* board, int playersTurn, ValidMoves validMoves, int alpha, int beta) {

    // If terminal state, return utility value of 0
    if (findValidMoves(board, playersTurn).size == 0) {
        return 0;
    }

    // Loop through valid moves
    for (int i = 0; i < validMoves.size; i++) {
        // Get the next state
        Board* nextState = minMaxResult(board, validMoves.moves[i]);

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

Move minimax(Board* board) {
    /*
    function MINIMAX-DECISION(state) returns an action
     inputs: state, current state in game
     v←MAX-VALUE(state)
     return the action in SUCCESSORS(state) with value v
    */

    // Find valid moves
    ValidMoves validMoves = findValidMoves(board);

    printf("===DEBUG===\n");
    printf("Valid moves: %d\n", validMoves.size);
    for (int i=0; i<validMoves.size; i++) {
        printf("Move: %c%d to %c%d\n", validMoves.moves[i].start.x, validMoves.moves[i].start.y, validMoves.moves[i].end.x, validMoves.moves[i].end.y);
    }
    printf("==/DEBUG===\n");

    // Initialize best move index
    int bestMoveIndex = -1;

    // Initialize max and min values
    // Max wants to maximize the total number of valid moves
    // Min wants to minimize the total number of valid moves
    int max = -1000; // Max is initialized to negative infinity
    int min = 1000; // Min is initialized to positive infinity

    // Loop through valid moves
    for (int i=0; i<validMoves.size; i++) {
        // Copy the board
        Board* nextState = copyBoard(board);

        // Make the move on the copy
        makeMove(nextState, validMoves.moves[i]);

        // Get the value of the next state
        int value;

        // If player is maximizing, get the max value
        if (board->player == MAXIMIZING_PLAYER) {
            // Get the max value
            value = maxValue(nextState, findValidMoves(nextState));
            
            // If value is greater than max, update max
            if (value > max) {
                max = value;
                bestMoveIndex = i;
            }
        } else if (board->player == MINIMIZING_PLAYER) {
            // Get the min value
            value = minValue(nextState, findValidMoves(nextState));

            // If value is less than min, update min
            if (value < min) {
                min = value;
            }
        }

        // Free the memory
        free(nextState);
    }

    // Return best move
    return validMoves.moves[bestMoveIndex];
}
