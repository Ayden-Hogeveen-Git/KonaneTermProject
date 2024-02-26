#include "structures.h"


/*
Initializes the game board.
param Board* board: 2D array representation of game board.
*/
void initializeBoard(Board* board);

/*
Prints the game board to the console.
param Board board: 2D array representation of game board.
*/
void printBoard(Board board);

/*
Copies the entire game board and returns the copy.
param Board* board: 2D array representation of game board.
*/
Board* copyBoard(Board* board);

/*
Converts a string to uppercase.
param char* str: string to convert to uppercase.
*/
void toUpper(char* str);

/*
Returns 1 if valid, 0 otherwise.
param Board* board: 2D array representation of game board.
param Point point: coordinates of the piece to remove.
*/
int isValidFirstMove(Board* board, Point point);

/*
Returns 1 if valid, 0 otherwise.
param Board* board: 2D array representation of game board.
param Move move: coordinates of the piece to move.
*/
int isValidMove(Board* board, Move move);

/*
Takes a position on the board and removes the piece at that position.
param Board* board: 2D array representation of game board.
param Point point: coordinates of the piece to remove.
*/
void makeFirstMove(Board* board, Point point);

/*
Takes a position on the board, a piece, and a new position and moves the piece to the new position.
param Board* board: 2D array representation of game board.
param Move move: coordinates of the piece to move.
*/
void makeMove(Board* board, Move move);

/*
Adds a move to the list of valid moves.
param ValidMoves* validMoves: list of valid moves.
param Move move: coordinates of the piece to move.
*/
void addMove(ValidMoves* validMoves, Move move);

/*
Returns a list of valid moves for a given player's turn.
param Board* board: 2D array representation of game board.
*/
ValidMoves findValidMoves(Board* board);
