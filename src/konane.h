#include "structures.h"


/*
Converts a direction to a string.
param Direction direction: The direction to convert to a string.
return char*: The string representation of the direction.
*/
char* directionToString(Direction direction);

/*
Converts a direction to an integer.
param Direction direction: The direction to convert to an integer.
return int: The integer representation of the direction.
*/
int directionToInt(Direction direction);

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
Converts the board state to a string.
param GameState* game: The representation of the current game state.
return char*: The string representation of the board state.
*/
char* gameStateToString(GameState* game);

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
Checks if it's a valid move or not.
param GameState* game: The representation of the current game state.
param Player player: The player to check the move for.
param Move move: The coordinates of the piece to move.
return int: 1 if valid, 0 otherwise.
*/
int isValidMove(GameState* game, Player player, Move move);

/*
Checks if it's the first move for black or white.
param GameState* game: The representation of the current game state.
return int: 1 if it's the first move, 0 otherwise.
*/
int isFirstMove(GameState* game);

/*
Toggles the player's turn and the min/max states related to the player.
param GameState* game: The representation of the current game state.
*/
void togglePlayer(GameState* game);

/*
Takes the game state and a move and moves the piece to the new position.
param GameState* game: The representation of the current game state.
param Move move: The coordinates of the piece to move.
*/
void makeMove(GameState* game, Move move);

/*
Formulates a left move based on the number of jumps and the current position.
param int jumps: The number of jumps.
param int x: The x-coordinate of the current position.
param int y: The y-coordinate of the current position.
return Move: The left move.
*/
Move getLeftMove(int jumps, int x, int y);

/*
Formulates a right move based on the number of jumps and the current position.
param int jumps: The number of jumps.
param int x: The x-coordinate of the current position.
param int y: The y-coordinate of the current position.
return Move: The right move.
*/
Move getRightMove(int jumps, int x, int y);

/*
Formulates an up move based on the number of jumps and the current position.
param int jumps: The number of jumps.
param int x: The x-coordinate of the current position.
param int y: The y-coordinate of the current position.
return Move: The up move.
*/
Move getUpMove(int jumps, int x, int y);

/*
Formulates a down move based on the number of jumps and the current position.
param int jumps: The number of jumps.
param int x: The x-coordinate of the current position.
param int y: The y-coordinate of the current position.
return Move: The down move.
*/
Move getDownMove(int jumps, int x, int y);

/*
Determines if the current node is a terminal node or not.
param Node* node: The representation of the current game state.
return int: 1 if terminal, 0 otherwise.
*/
int isTerminal(Node* node);

/*
Counts the number of valid moves for a given player in the current game state.
param GameState* game: The representation of the current game state.
param Player player: The player to count the valid moves for.
return int: The number of valid moves for a given player in the current game state.
*/
int countValidMoves(GameState* game, Player player);

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

/*
Frees the minimax tree.
param Node* node: The parent node.
*/
void freeTree(Node* node);
