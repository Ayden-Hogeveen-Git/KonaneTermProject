/*
Prints the game board to the console
param char** board: 2D array representation of game board
*/
void printBoard(char board[8][8]);


/*
Takes a position on the board, a piece, and a new position and moves the piece to the new position
param int team: 0 for black, 1 for white
param int x: x coordinate of the piece to move
param int y: y coordinate of the piece to move
param int newX: x coordinate of the new position
param int newY: y coordinate of the new position
param char** board: 2D array representation of game board
*/
void makeMove(int team, int x, int y, int newX, int newY, char board[8][8]);


/*
Returns 1 if valid, 0 otherwise
param int x: x coordinate of the piece to move
param int y: y coordinate of the piece to move
param int newX: x coordinate of the new position
param int newY: y coordinate of the new position
param char** board: 2D array representation of game board
*/
int isValidMove(int x, int y, int newX, int newY, char board[8][8]);
