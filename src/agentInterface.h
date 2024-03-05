#include <stdio.h>
#include "structures.h"


/*
Logs the move to the logging file.
param FILE* file: The file to log to.
param Move* move: The move to be logged.
*/
void logMove(FILE* file, Move* move);

/*
Logs the game state to the logging file.
param FILE* file: The file to log to.
param GameState* game: The representation of the current game state.
*/
void logGameState(FILE* file, GameState* game);

/*
Determines and sets player's turn based on the current state of the game.
param GameState* game: The game state as a struct.
param char player: The player represented as a character.
*/
void setPlayersTurn(GameState* game, char player);

/*
Formats the incoming game string by removing all non-alphabetical characters.
param char* game: The game state as a string.
return char*: The formatted game state as a string.
*/
char* formatGameString(char* game);

/*
Initializes the game state from string into a GameState struct.
param char* gameString: The game state as a string.
param char* player: The player represented as a character.
return GameState*: The game state as a struct.
*/
GameState* initalizeGameState(char* gameString, char player);

/*
Prints the agent's chosen move to standard output.
param Move* move: The move to be outputted.
*/
void agentOutput(Move* move);
