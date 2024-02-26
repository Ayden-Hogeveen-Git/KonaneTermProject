#include "structures.h"


/*
Returns the minimum value of two integers
*/
int min(int a, int b);

/*
Returns the maximum value of two integers
*/
int max(int a, int b);

/*
Returns the minimum utility value of the game board's state
*/
int minValue(Board* board, int playersTurn, ValidMoves validMoves);

/*
Returns the maximum utility value of the game board's state
*/
int maxValue(Board* board, int playersTurn, ValidMoves validMoves);

/*
Returns the best move for the current player using the minimax algorithm
*/
Move minimax(Board* board, int playersTurn);
