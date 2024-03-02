#include "structures.h"


/*
Returns the minimum value of two integers.
param int a: First integer.
param int b: Second integer.
*/
int min(int a, int b);

/*
Returns the maximum value of two integers.
param int a: First integer.
param int b: Second integer.
*/
int max(int a, int b);

/*
Returns the minimum utility value of a given game state.
param GameState* game: The representation of the current game state.
param ValidMoves validMoves: list of valid moves.
param Depth: The depth limit of the minimax tree.
*/
int minValue(GameState* game, ValidMoves validMoves, int depth);

/*
Returns the maximum utility value of a given game state.
param GameState* game: The representation of the current game state.
param ValidMoves validMoves: list of valid moves.
param Depth: The depth limit of the minimax tree.
*/
int maxValue(GameState* game, ValidMoves validMoves, int depth);

/*
Returns the minimum utility value of a given game state.
param GameState* game: The representation of the current game state.
param Depth: The depth limit of the minimax tree.
*/
int minValueNew(GameState* game, int depth);

/*
Returns the maximum utility value of a given game state.
param GameState* game: The representation of the current game state.
param Depth: The depth limit of the minimax tree.
*/
int maxValueNew(GameState* game, int depth);

/*
Returns the best move for the current player using the minimax algorithm.
param GameState* game: The representation of the current game state.
*/
Move minimax(GameState* game);

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
