#include "structures.h"


/*
Determines the first move for the current player at random.
param GameState* game: The representation of the current game state.
return Move: The first move for the current player at random.
*/
Move chooseFirstMove(GameState* game);

/*
Returns the minimum value of two integers.
param int a: First integer.
param int b: Second integer.
return int: The minimum value of two integers.
*/
int min(int a, int b);

/*
Returns the maximum value of two integers.
param int a: First integer.
param int b: Second integer.
return int: The maximum value of two integers.
*/
int max(int a, int b);

/*
Determines the best move for the current player using the minimax algorithm with alpha-beta pruning.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
param int alpha: The alpha value for alpha-beta pruning.
param int beta: The beta value for alpha-beta pruning.
param Move* bestMove: The best move for the current player using the minimax algorithm with alpha-beta pruning.
return int: The utility value of the best move for the current player using the minimax algorithm with alpha-beta pruning.
*/
int minimaxAlphaBeta(Node* node, int depth, int alpha, int beta, Move* bestMove);
