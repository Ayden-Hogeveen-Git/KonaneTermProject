#include <stdio.h>
#include "structures.h"


/*
Opens the logging file.
return FILE*: A pointer to the logging file.
*/
FILE* openLogFile();

/*
Logs the string to the logging file.
param char* string: The string to be logged.
*/
void logString(char* string);

/*
Logs the string and integer to the logging file.
param char* string: The string to be logged.
param int value: The integer to be logged.
*/
void logStringWithInt(char* string, int value);

/*
Logs the game state to the logging file.
param GameState* game: The representation of the current game state.
param Move move: The move made by the player.
*/
void logGameState(GameState* game, Move move);
