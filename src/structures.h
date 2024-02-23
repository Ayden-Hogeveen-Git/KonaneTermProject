#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    char x;
    int y;
} Point;

typedef struct {
    Point start;
    Point end;
} Move;

typedef struct {
    Move* moves;
    int capacity;
    int size;
} ValidMoves;

typedef struct {
    char board[8][8];
} Board;

typedef struct Node {
    Board board;
    struct Node* children;
    int numChildren;
} Node;

#endif
