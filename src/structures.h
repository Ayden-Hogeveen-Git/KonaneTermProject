#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum { MAXIMIZING_PLAYER, MINIMIZING_PLAYER } Player;

#define MAX_DEPTH 10

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
    Point position;
    char piece; // 'B' for black, 'W' for white, 'O' for empty
} Piece;

typedef struct {
    Piece state[8][8];
    Player player;
} Board;

typedef struct Node {
    Board board;
    struct Node* children;
    int numChildren;
} Node;

#endif
