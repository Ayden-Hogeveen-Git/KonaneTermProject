#include <stdio.h>
#include <stdlib.h>


void printBoard(char board[8][8]) {
    for (int x=0; x<8; x++) {
        for (int y=0; y<8; y++) {
            printf("%c ", board[x][y]);
        }
        printf("\n");
    }
}


void makeMove(int team, int x, int y, int newX, int newY, char board[8][8]) {
    board[newX][newY] = board[x][y];
    board[x][y] = ' ';
    board[(x+newX)/2][(y+newY)/2] = ' ';
}


int isValidMove(int x, int y, int newX, int newY, char board[8][8]) {
    if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
        return 0;
    }
    if (abs(newX - x) != 2 && abs(newY - y) != 2) {
        return 0;
    }
    return 1;
}
