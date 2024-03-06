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
Calculates how many pieces are on the board for each player.
param Node* node: The representation of the current game state.
return int: The difference between the number of pieces for each player.
*/
int evalCountBW(Node* node);

/*
Calculates the difference between the valid moves for the current player and the opponent.
param Node* node: The representation of the current game state.
return int: The difference between the valid moves for the current player and the opponent.
*/
int evalCalcMobility(Node* node);

/*
Calculates the respective utility value of a given game state.
param Node* node: The representation of the current game state.
param int type: The type of the evaluation function.
return int: The respective utility value of a given game state.
*/
int evaluationFunction(Node* node, int type);

/*
Determines the best move for the current player using the minimax algorithm.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
param Move* bestMove: The best move for the current player using the minimax algorithm.
return int: The utility value of the best move for the current player using the minimax algorithm.
*/
int minimax(Node* node, int depth, Move* bestMove);

/*
Determines the best move for the current player using the minimax algorithm with alpha-beta pruning.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
param int alpha: The alpha value for alpha-beta pruning.
param int beta: The beta value for alpha-beta pruning.
param Move* bestMove: The best move for the current player using the minimax algorithm with alpha-beta pruning.
*/
int minimaxAlphaBeta(Node* node, int depth, int alpha, int beta, Move* bestMove);
