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
Calculates how many pieces are on the board for each player.
param GameState* game: The representation of the current game state.
return int: The difference between the number of pieces for each player.
*/
int evalCountBW(GameState* game);

/*
Calculates the mobility of a given player.
param GameState* game: The representation of the current game state.
param Player player: The player to calculate the mobility for.
return int: The mobility of a given player.
*/
int calculateMobility(GameState* game, Player player);

/*
Calculates the utility value of a given game state.
param GameState* game: The representation of the current game state.
return int: The utility value of a given game state.
*/
int evaluateGameState(GameState* game);

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
Calculates the minimum utility value of a given game state.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
return int: The minimum utility value of a given game state.
*/
int minValue(Node* node, int depth);

/*
Calculates the maximum utility value of a given game state.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
return int: The maximum utility value of a given game state.
*/
int maxValue(Node* node, int depth);

/*
Calculates the minimum utility value of a given game state using alpha-beta pruning.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
param int* alpha: The alpha value of the alpha-beta pruning algorithm.
param int* beta: The beta value of the alpha-beta pruning algorithm.
return int: The minimum utility value of a given game state.
*/
int minValueAlphaBeta(Node* node, int depth, int* alpha, int* beta);

/*
Calculates the maximum utility value of a given game state using alpha-beta pruning.
param Node* node: The representation of the current game state.
param int depth: The depth limit of the minimax tree.
param int* alpha: The alpha value of the alpha-beta pruning algorithm.
param int* beta: The beta value of the alpha-beta pruning algorithm.
return int: The maximum utility value of a given game state.
*/
int maxValueAlphaBeta(Node* node, int depth, int* alpha, int* beta);

/*
Determines the best move for the current player using the minimax algorithm.
param GameState* game: The representation of the current game state.
return Move: The best move for the current player using the minimax algorithm.
*/
Move minimax(GameState* game);

/*
Determines the best move for the current player using the minimax algorithm with alpha-beta pruning.
param GameState* game: The representation of the current game state.
return Move: The best move for the current player using the minimax algorithm with alpha-beta pruning.
*/
Move minimaxAlphaBeta(GameState* game);
