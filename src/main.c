#include "konane.h"
#include <stdlib.h>
#include <stdio.h>


int main() {
    // Game Variables
    int running = 1; 
    int firstX, firstY, secondX, secondY;  // Coordinates of the first two moves
    int move = 0;  // 0 for black, 1 for white -- black moves first
    char board[8][8] = {
        {'x', 'o', 'x', 'o', 'x', 'o', 'x', 'o'},
        {'o', 'x', 'o', 'x', 'o', 'x', 'o', 'x'},
        {'x', 'o', 'x', 'o', 'x', 'o', 'x', 'o'},
        {'o', 'x', 'o', 'x', 'o', 'x', 'o', 'x'},
        {'x', 'o', 'x', 'o', 'x', 'o', 'x', 'o'},
        {'o', 'x', 'o', 'x', 'o', 'x', 'o', 'x'},
        {'x', 'o', 'x', 'o', 'x', 'o', 'x', 'o'},
        {'o', 'x', 'o', 'x', 'o', 'x', 'o', 'x'}
    };

    // First Moves
    printf("Initial board:\n");
    printBoard(board);

    printf("Enter the x and y of the piece you want to remove: ");
    scanf("%d %d", &firstX, &firstY);
    makeMove(move, firstX, firstY, firstX, firstY, board);
    printBoard(board);

    printf("Enter the x and y of the piece you want to remove: ");
    scanf("%d %d", &secondX, &secondY);
    makeMove(move, secondX, secondY, secondX, secondY, board);
    printBoard(board);

    // Main Game Loop
    while (running == 1) {
        int x, y, newX, newY;
        if (move == 0) {
            printf("Black's move\n");
        } else {
            printf("White's move\n");
        }

        printf("Enter the x and y coordinates of the piece you want to move: ");
        scanf("%d %d", &x, &y);
        printf("Enter the x and y coordinates of the new position: ");
        scanf("%d %d", &newX, &newY);

        // Exit with "-1"
        if (newX == -1 || newY == -1)
            running = 0;

        // Check if move is valid
        if (isValidMove(x, y, newX, newY, board) == 0)
            printf("Invalid move\n");
        else {
            makeMove(move, x, y, newX, newY, board);

            printBoard(board);
            move = (move + 1) % 2;
        }
    }

    return 0;
}