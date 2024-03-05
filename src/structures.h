#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum { BLACK, WHITE, EMPTY } Player;

#define MAX_DEPTH 1
#define THINKINGTIME 20

typedef struct {
    char x;
    int y;
} Point;

typedef struct {
    Point start;
    Point end;
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
} Node;

#endif
