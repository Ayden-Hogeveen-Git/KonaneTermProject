#include "structures.h"


/*
Calculates how many pieces are on the board for each player.
param Node* node: The representation of the current game state.
return int: The difference between the number of pieces for each player.
*/
int evalCountBW(Node* node);

/*
Calculates how many siblings the current node has.
param Node* node: The representation of the current game state.
return int: The number of siblings the current node has.
*/
int evalCountSiblings(Node* node);

/*
Calculates how many children the current node has, including all decendents.
param Node* node: The representation of the current game state.
return int: The number of children the current node has, including all decendents.
*/
int evalCountChildren(Node* node);

/*
Calculates the respective utility value of a given game state.
param Node* node: The representation of the current game state.
param int type: The type of the evaluation function.
return int: The respective utility value of a given game state.
*/
int evaluationFunction(Node* node, int type);