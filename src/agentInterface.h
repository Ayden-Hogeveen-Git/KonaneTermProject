#include <stdio.h>
#include "structures.h"


/*
Logs the string to the logging file.
param char* string: The string to be logged.

*/
void logString(char* string);

/*
Logs the player's move to the logging file.
param GameState* game: The representation of the current game state.
param Move move: The move made by the player.
*/
void logPlayerMove(GameState* game, Move move);

/*
Logs the game state to the logging file.
param GameState* game: The representation of the current game state.
param Move move: The move made by the player.
*/
void logGameState(GameState* game, Move move);

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

/*
Gets the opponent's move from standard input.
param GameState* game: The representation of the current game state.
param char* nextMoveString: The string representation of the next move.
return Move: The opponent's move.
*/
Move getOpponentMove(GameState* game, char* nextMoveString);
