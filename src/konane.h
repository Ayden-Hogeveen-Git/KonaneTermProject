#include "structures.h"


/*
Converts a string to uppercase.
param char* str: String to convert to uppercase.
*/
void coordToUpper(char* str);

/*
Converts a Player enum to a char ('B', 'W', or 'O').
param Player piece: The piece type to convert to a char.
return char: The char representation of the piece type.
*/
char pieceToChar(Player piece);

/*
Prints the game board to the console.
param GameState game: The representation of the current game state.
*/
void printBoard(GameState* game);

/*
Initializes the board.
param GameState* game: The representation of the current game state.
*/
void initializeBoard(GameState* game);

/*
Initializes the game state.
*/
GameState* initializeGameState();

/*
Copies the entire game board and returns the copy.
param GameState* game: The representation of the current game state.
*/
GameState* copyGameState(GameState game);

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
Adds a valid move to the list of valid moves.
param ValidMoves* validMoves: list of valid moves.
param Move move: coordinates of the piece to move.
*/
void addValidMove(ValidMoves* validMoves, Move move);

/*
Returns 1 if the game is over, 0 otherwise.
param GameState* game: The representation of the current game state.
*/
int isFirstMove(GameState* game);

/*
Toggles the player's turn and the min/max states related to the player.
param GameState* game: The representation of the current game state.
*/
void togglePlayer(GameState* game);

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

/*
Adds a move to the list of valid moves.
param ValidMoves* validMoves: list of valid moves.
param Move move: coordinates of the piece to move.
*/
void addMove(ValidMoves* validMoves, Move move);

/*
Returns a list of valid moves for a given player's turn.
param GameState* game: 2D array representation of game game.
*/
ValidMoves findValidMoves(GameState* game);

/*
Frees the memory allocated for the list of valid moves.
param ValidMoves* validMoves: list of valid moves.
*/
void freeValidMoves(ValidMoves* validMoves);

/*
Adds a child node to the parent node by making a move.
param Node* node: The parent node.
param Move move: The move to make.
*/
void addChild(Node* node, Move move);

/*
Generates the children of a given node by finding all valid moves.
param Node* node: The parent node.
*/
void generateChildren(Node* node);
