#include "structures.h"


/*
Determines which player's turn it is based on the current state of the game.
param GameState* game: the game game
*/
int whoseTurn(GameState* game);

/*
Initializes the game state from string into a GameState struct.
param char* game: the game state as a string.
*/
GameState* initalizeGame(char* game);

/*
Outputs the agent's chosen move to standard output.
param Move* move: the move to be outputted.
*/
void outputMove(Move* move);
