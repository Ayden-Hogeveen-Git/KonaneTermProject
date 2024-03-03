#include "structures.h"


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
Returns the minimum utility value of a given game state.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
return int: The minimum utility value of a given game state.
*/
int minValue(Node* node, int depth);

/*
Returns the maximum utility value of a given game state.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
return int: The maximum utility value of a given game state.
*/
int maxValue(Node* node, int depth);

/*
Returns the minimum utility value of a given game state using alpha-beta pruning.
param GameState* game: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
param int alpha: The alpha value of the alpha-beta pruning algorithm.
param int beta: The beta value of the alpha-beta pruning algorithm.
return int: The minimum utility value of a given game state.
*/
int minValueAlphaBeta(GameState* game, ValidMoves validMoves, int depth, int alpha, int beta);

/*
Returns the maximum utility value of a given game state using alpha-beta pruning.
param GameState* game: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
param int alpha: The alpha value of the alpha-beta pruning algorithm.
param int beta: The beta value of the alpha-beta pruning algorithm.
return int: The maximum utility value of a given game state.
*/
int maxValueAlphaBeta(GameState* game, ValidMoves validMoves, int depth, int alpha, int beta);

/*
Returns the minimum utility value of a given game state using alpha-beta pruning.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
param int alpha: The alpha value of the alpha-beta pruning algorithm.
param int beta: The beta value of the alpha-beta pruning algorithm.
*/
int minValueAlphaBetaNew(Node* node, int depth, int alpha, int beta);

/*
Returns the maximum utility value of a given game state using alpha-beta pruning.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
param int alpha: The alpha value of the alpha-beta pruning algorithm.
param int beta: The beta value of the alpha-beta pruning algorithm.
*/
int maxValueAlphaBetaNew(Node* node, int depth, int alpha, int beta);

/*
Returns the best move for the current player using the minimax algorithm.
param GameState* game: The representation of the current game state.
*/
Move minimax(GameState* game);

/*
Returns the best move for the current player using the minimax algorithm with alpha-beta pruning.
param GameState* game: The representation of the current game state.
*/
Move minimaxAlphaBeta(GameState* game);

/*
Returns the best move for the current player using the minimax algorithm with alpha-beta pruning.
param GameState* game: The representation of the current game state.
*/
Move minimaxAlphaBetaNew(GameState* game);
