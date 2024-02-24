#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
// #include "konane.h"


void makeMove(Board* board, Move move) {
    // Convert the x coordinates from A-H to 0-7
    int oldX = move.start.x - 'A';
    int newXIndex = move.end.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int oldY = move.start.y - 1;
    int newYIndex = move.end.y - 1;

    // Make the move
    board->board[newXIndex][newYIndex] = board->board[oldX][oldY];
    board->board[oldX][oldY] = ' ';
    board->board[(oldX + newXIndex) / 2][(oldY + newYIndex) / 2] = ' ';

    // board->board[newX][newY] = board->board[x][y];
    // board->board[x][y] = ' ';
    // board->board[(x + newX) / 2][(y + newY) / 2] = ' ';
}

int isValidMove(Board* board, Move move) {
    if (move.end.x < 'A' || move.end.x > 'H' || move.end.y < 1 || move.end.y > 8) {
        return 0;
    }
    if (abs(move.end.x - move.start.x) != 2 && abs(move.end.y - move.start.y) != 2) {
        return 0;
    }
    return 1;
}

void addValidMove(ValidMoves* validMoves, Move move) {
    // If the valid moves array is full, double the capacity
    if (validMoves->size == validMoves->capacity) {
        validMoves->capacity *= 2;
        validMoves->moves = realloc(validMoves->moves, validMoves->capacity * sizeof(Move));
    }

    // Add the valid move to the array
    validMoves->moves[validMoves->size] = move;
    validMoves->size++;
}

ValidMoves findValidMoves(Board* board) {
    // Initialize the valid moves array
    ValidMoves validMoves;
    validMoves.capacity = 10;

    // Allocate memory for valid moves array
    validMoves.moves = malloc(validMoves.capacity * sizeof(Move));
    
    // Check if memory allocation failed or not
    if (validMoves.moves == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize valid moves array
    validMoves.size = 0;

    // Find valid moves
    int index = 0;
    for (char x='A'; x<='H'; x++) {
        for (int y=0; y<8; y++) {
            if (board->board[x][y] == 'B') {
                // Check if the piece can move to the right
                Move moveRight = {x, y, x+2, y};
                if (isValidMove(board, moveRight) == 1) {
                    addValidMove(&validMoves, moveRight);
                    index++;
                }

                // Check if the piece can move to the left
                Move moveLeft = {x, y, x-2, y};
                if (isValidMove(board, moveLeft) == 1) {
                    addValidMove(&validMoves, moveLeft);
                    index++;
                }

                // Check if the piece can move up
                Move moveUp = {x, y, x, y+2};
                if (isValidMove(board, moveUp) == 1) {
                    addValidMove(&validMoves, moveUp);
                    index++;
                }

                // Check if the piece can move down
                Move moveDown = {x, y, x, y-2};
                if (isValidMove(board, moveDown) == 1) {
                    addValidMove(&validMoves, moveDown);
                    index++;
                }
            }
        }
    }

    // Return valid moves array
    return validMoves;
}

int minMaxResult(Board* board, Move move) {
    // Make the move
    makeMove(board, move);

    // Return the new state
    return board;
}

int minValue(Board* board, ValidMoves validMoves) {
    /*
    function MIN-VALUE(state) returns a utility value
     if TERMINAL-TEST(state) then return UTILITY(state)
     v ← ∞
     for a,s in SUCCESSORS(state) do
     v ← MIN(v,MAX-VALUE(s))
     return v
    */

    // If terminal state, return utility value
    if (findValidMoves(board).size == 0) {
        return 0;
    }

    // Initialize v to positive infinity
    int v = 1000;

    // Loop through valid moves
    for (int i=0; i<validMoves.size; i++) {
        // Get the next state
        Board* nextState = minMaxResult(board, validMoves.moves[i]);

        // Get the max value
        v = min(v, maxValue(nextState, findValidMoves(nextState)));
    }

    // Return v
    return v;
}

int maxValue(Board* board, ValidMoves validMoves) {
    /*
    function MAX-VALUE(state) returns a utility value
     if TERMINAL-TEST(state) then return UTILITY(state)
     v ← - ∞
     for a,s in SUCCESSORS(state) do
     v ← MAX(v,MIN-VALUE(s))
     return v
     */

    // If terminal state, return utility value
    if (terminalTest(board) == 1) {
        return utility(board);
    }

    // Initialize v to negative infinity
    int v = -1000;

    // Loop through valid moves
    for (int i=0; i<validMoves.size; i++) {
        // Get the next state
        Board* nextState = minMaxResult(board, validMoves.moves[i]);

        // Get the min value
        v = max(v, minValue(nextState, findValidMoves(nextState)));
    }

    // Return v
    return v;
}

Move minimax(Board* board) {
    /*
    function MINIMAX-DECISION(state) returns an action
     inputs: state, current state in game
     v←MAX-VALUE(state)
     return the action in SUCCESSORS(state) with value v
    */

    // Find valid moves
    ValidMoves validMoves = findValidMoves(board);

    // Initialize best move index
    int bestMoveIndex = -1;

    // Initialize max and min values
    // Max (this agent) wants to maximize the total number of valid moves
    // Min (opponent) wants to minimize the total number of valid moves
    int max = -1000; // Max is initialized to negative infinity
    int min = 1000; // Min is initialized to positive infinity

    // Loop through valid moves
    for (int i=0; i<validMoves.size; i++) {
        // Get the next state
        Board* nextState = minMaxResult(board, validMoves.moves[i]);

        // Get the min value
        int minValueResult = minValue(nextState, findValidMoves(nextState));

        // If min value is less than min, update min
        if (minValueResult < min) {
            min = minValueResult;
        }

        // If min value is greater than max, update max and best move index
        if (minValueResult > max) {
            max = minValueResult;
            bestMoveIndex = i;
        }
    }

    // Return best move
    return validMoves.moves[bestMoveIndex];
}
