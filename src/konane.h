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
return GameState*: The representation of the current game state.
*/
GameState* initializeGameState();

/*
Copies the entire game board and returns the copy.
param GameState* game: The representation of the current game state.
return GameState*: The copy of the game board.
*/
GameState* copyGameState(GameState game);

/*
Checks if it's a valid first move or not.
param GameState* game: The representation of the current game state.
param Point point: The coordinates of the piece to remove.
return int: 1 if valid, 0 otherwise.
*/
int isValidFirstMove(GameState* game, Point point);

/*
Checks if it's a valid move or not.
param GameState* game: The representation of the current game state.
param Move move: The coordinates of the piece to move.
return int: 1 if valid, 0 otherwise.
*/
int isValidMove(GameState* game, Player player, Move move, int jumps);

/*
Checks if it's the first move for black or white.
param GameState* game: The representation of the current game state.
param int* firstMoveFlag: The flag to check if it's the first move.
*/
void isFirstMove(GameState* game, int* firstMoveFlag);

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
TODO
*/
Move getLeftMove(int jumps, int x, int y);

/*
TODO
*/
Move getRightMove(int jumps, int x, int y);

/*
TODO
*/
Move getUpMove(int jumps, int x, int y);

/*
TODO
*/
Move getDownMove(int jumps, int x, int y);

/*
Determines if the current node is a terminal node or not.
param Node* node: The representation of the current game state.
return int: 1 if terminal, 0 otherwise.
*/
int isTerminal(Node* node);

/*
Checks if the game is over or not. If so it updates the winner in the game state.
param GameState* game: The representation of the current game state.
*/
void checkForWinner(GameState* game);

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

/*
Generates the minimax tree for a given node.
param Node* node: The parent node.
param int depth: The depth limit of the minimax tree.
*/
void generateTree(Node* node, int depth);
