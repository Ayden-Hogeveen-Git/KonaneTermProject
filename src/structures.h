#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum { MAXIMIZING_PLAYER, MINIMIZING_PLAYER } Player;
typedef enum { BLACK, WHITE, EMPTY } PieceType;

#define MAX_DEPTH 10
#define MAX_MOVES 32
#define THINKINGTIME 10

typedef struct {
    char x;
    int y;
} Point;

typedef struct {
    Point start;
    Point end;
} Move;

// typedef struct {
//     Move* moves;
//     int capacity;
//     int size;
// } ValidMoves;

typedef struct {
    Point position; // Probably not needed
    PieceType piece; // 'B' for black, 'W' for white, 'O' for empty
} Cell;

typedef struct {
    Move prevMove;
    Cell board[8][8];
    Player player;
    Player winner;
} GameState;

typedef struct Node {
    GameState game;
    struct Node* children;
    int capacity;
    int size;
} Node;

#endif
