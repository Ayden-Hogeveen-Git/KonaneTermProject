#include "structures.h"


/*
Returns the minimum value of two integers.
param int a: first integer.
param int b: second integer.
*/
int min(int a, int b);

/*
Returns the maximum value of two integers.
param int a: first integer.
param int b: second integer.
*/
int max(int a, int b);

/*
Returns the minimum utility value of the game board's state.
param Board* board: 2D array representation of game board.
param ValidMoves validMoves: list of valid moves.
*/
int minValue(Board* board, ValidMoves validMoves);

/*
Returns the maximum utility value of the game board's state.
param Board* board: 2D array representation of game board.
param ValidMoves validMoves: list of valid moves.
*/
int maxValue(Board* board, ValidMoves validMoves);

/*
Returns the best move for the current player using the minimax algorithm.
param Board* board: 2D array representation of game board.
*/
Move minimax(Board* board);
