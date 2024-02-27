#include "structures.h"


/*
Initializes the game state.
param GameState* game: The representation of the current game state.
*/
void initializeBoard(GameState* game);

/*
Prints the game board to the console.
param GameState game: The representation of the current game state.
*/
void printBoard(GameState game);

/*
Copies the entire game board and returns the copy.
param GameState* game: The representation of the current game state.
*/
GameState* copyBoard(GameState* game);

/*
Converts a string to uppercase.
param char* str: String to convert to uppercase.
*/
void toUpper(char* str);

/*
Returns 1 if valid, 0 otherwise.
param GameState* game: The representation of the current game state.
param Point point: The coordinates of the piece to remove.
*/
int isValidFirstMove(GameState* game, Point point);

/*
Returns 1 if valid, 0 otherwise.
param GameState* game: The representation of the current game state.
param Move move: The coordinates of the piece to move.
*/
int isValidMove(GameState* game, Move move);

/*
Takes the game state and a point and removes the piece at that position.
param GameState* game: The representation of the current game state.
param Point point: The coordinates of the piece to remove.
*/
void makeFirstMove(GameState* game, Point point);

/*
Takes the game state and a move and moves the piece to the new position.
param GameState* game: The representation of the current game state.
param Move move: The coordinates of the piece to move.
*/
void makeMove(GameState* game, Move move);

// /*
// Adds a move to the list of valid moves.
// param ValidMoves* validMoves: list of valid moves.
// param Move move: coordinates of the piece to move.
// */
// void addMove(ValidMoves* validMoves, Move move);

// /*
// Returns a list of valid moves for a given player's turn.
// param GameState* game: 2D array representation of game game.
// */
// ValidMoves findValidMoves(GameState* game);

// /*
// Frees the memory allocated for the list of valid moves.
// param ValidMoves* validMoves: list of valid moves.
// */
// void freeValidMoves(ValidMoves* validMoves);
