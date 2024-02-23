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
    char x[8];
    char y[8];
} Board;

#endif
