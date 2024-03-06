#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum { BLACK, WHITE, EMPTY } Player;
typedef enum { LEFT, RIGHT, UP, DOWN, FIRST } Direction;

#define MAX_SEARCH_DEPTH 100
#define MAX_TREE_DEPTH 100
#define THINKINGTIME 20

typedef struct {
    char x;
    int y;
} Point;

typedef struct {
    Point start;
    Point end;
    Direction direction;
    int jumps;
} Move;

typedef struct {
    Player board[8][8];
    int firstMove;
    Move prevMove;
    Player turn;
    Player maxPlayer;
    Player minPlayer;
    Player winner;
} GameState;

typedef struct Node {
    GameState game;
    struct Node** children;
    int capacity;
    int size;
    int depth;
} Node;

#endif
