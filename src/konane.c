#include <stdlib.h>
#include <stdio.h>
#include "structures.h"


void coordToUpper(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}

char pieceToChar(Player piece) {
    switch (piece) {
        case BLACK:
            return 'B';
        case WHITE:
            return 'W';
        case EMPTY:
            return 'O';
        default:
            return '?';
    }
}

void printBoard(GameState* game) {
    printf("\n  A B C D E F G H\n");
    for (int y = 8; y > 0; y--) {
        printf("%d ", y);
        for (int x = 0; x < 8; x++) {
            // printf("%c ", pieceToChar(game->board[y - 1][x].piece));
            printf("%c ", pieceToChar(game->board[y - 1][x]));
        }
        printf("%d\n", y);
    }
    printf("  A B C D E F G H\n\n");
}

void initializeBoard(GameState* game) {
    // Initialize the game board
    for (int y = 8; y > 0; y--) {
        for (int x = 0; x < 8; x++) {
            // game->board[y - 1][x].piece = (y + x) % 2 == 0 ? BLACK : WHITE;
            // game->board[y - 1][x].position.x = x;
            // game->board[y - 1][x].position.y = y;
            game->board[y - 1][x] = (y + x) % 2 == 0 ? BLACK : WHITE;
        }
    }

}

GameState* initializeGameState() {
    // Allocate memory for the game
    GameState* game = malloc(sizeof(GameState));

    // Check if memory allocation failed or not
    if (game == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize the game board
    initializeBoard(game);

    // Set the player to black and maximizer
    game->turn = BLACK;
    game->maxPlayer = BLACK;
    game->minPlayer = WHITE;

    // Set the winner to empty
    game->winner = EMPTY;

    // Return the game state
    return game;
}

GameState* copyGameState(GameState* game) {
    // Allocate memory for the new game
    GameState* newGame = malloc(sizeof(GameState));

    // Check if memory allocation failed or not
    if (newGame == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Copy the game board state
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            newGame->board[y][x] = game->board[y][x];
        }
    }

    // Copy the first move flag
    newGame->firstMove = game->firstMove;

    // Copy the previous move
    newGame->prevMove = game->prevMove;

    // Copy the player info
    newGame->turn = game->turn;
    newGame->maxPlayer = game->maxPlayer;
    newGame->minPlayer = game->minPlayer;

    // Copy the winner
    newGame->winner = game->winner;

    // Return the new game state
    return newGame;
}

int isValidFirstMove(GameState* game, Point point) {
    // Convert the x coordinates from A-H to 0-7
    int x = point.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int y = point.y - 1;

    // Check if the start coordinates are within the board starting area
    if (x < 3 || x > 4 || y < 3 || y > 4) {
        return 0;
    }

    // Check if the player is moving their own piece
    // if (game->turn == BLACK && game->board[y][x].piece != BLACK) {
    //     return 0;
    // } else if (game->turn == WHITE && game->board[y][x].piece != WHITE) {
    //     return 0;
    // }
    if (game->turn == BLACK && game->board[y][x] != BLACK) {
        return 0;
    } else if (game->turn == WHITE && game->board[y][x] != WHITE) {
        return 0;
    }

    return 1;
}

int isValidMove(GameState* game, Move move) {
    // Convert the x coordinates from A-H to 0-7
    int x = move.start.x - 'A';
    int newX = move.end.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int y = move.start.y - 1;
    int newY = move.end.y - 1;

    // Check if the start coordinates are within the game board
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return 0;
    }

    // Check if the end coordinates are within the game board
    if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
        return 0;
    }

    // Check if the piece is moving to an empty space
    // if (game->board[newY][newX].piece != EMPTY) {
    //     return 0;
    // }
    if (game->board[newY][newX] != EMPTY) {
        return 0;
    }

    // Check if the piece is moving to a valid space
    if (abs(newY - y) != 2 && abs(newX - x) != 2) {
        return 0;
    }

    // Check if the player is moving their own piece
    // if (game->turn == BLACK && game->board[y][x].piece != BLACK) {
    //     return 0;
    // } else if (game->turn == WHITE && game->board[y][x].piece != WHITE) {
    //     return 0;
    // }
    if (game->turn == BLACK && game->board[y][x] != BLACK) {
        return 0;
    } else if (game->turn == WHITE && game->board[y][x] != WHITE) {
        return 0;
    }

    // Check if the player is jumping over an opponent's piece
    // if (game->turn == BLACK && game->board[(y + newY) / 2][(x + newX) / 2].piece != WHITE) {
    //     return 0;
    // } else if (game->turn == WHITE && game->board[(y + newY) / 2][(x + newX) / 2].piece != BLACK) {
    //     return 0;
    // }
    if (game->turn == BLACK && game->board[(y + newY) / 2][(x + newX) / 2] != WHITE) {
        return 0;
    } else if (game->turn == WHITE && game->board[(y + newY) / 2][(x + newX) / 2] != BLACK) {
        return 0;
    }

    return 1;
}

void addValidMove(ValidMoves* validMoves, Move move) {
    // If the valid moves array is full, double the capacity
    if (validMoves->size == validMoves->capacity) {
        validMoves->capacity *= 2;
        validMoves->moves = realloc(validMoves->moves, validMoves->capacity * sizeof(Move));

        // Check if memory allocation failed or not
        if (validMoves->moves == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    // Add the valid move to the array
    validMoves->moves[validMoves->size] = move;
    validMoves->size++;
}

int isFirstMove(GameState* game) {
    // Initialize the empty counter
    int emptyCounter = 0;

    // Count the number of empty spaces, if there are less than 2, then it's the first move
    for (int y = 8; y > 0; y--) {
        for (int x = 0; x < 8; x++) {
            // if (game->board[y - 1][x].piece == EMPTY) {
            //     emptyCounter++;
            // }
            if (game->board[y - 1][x] == EMPTY) {
                emptyCounter++;
            }
            // Exit early if there are 2 or more empty spaces
            if (emptyCounter >= 2) {
                // Set the first move flag to 0
                game->firstMove = 0;
                return 0;
            }
        }
    }
    // If there are less than 2 empty spaces, then it's the first move
    return emptyCounter < 2;
}

void togglePlayer(GameState* game) {
    game->turn = (game->turn == BLACK) ? WHITE : BLACK;
    game->maxPlayer = (game->maxPlayer == BLACK) ? WHITE : BLACK;
    game->minPlayer = (game->minPlayer == BLACK) ? WHITE : BLACK;
}

void makeFirstMove(GameState* game, Point point) {
    // Convert the x coordinates from A-H to 0-7
    int x = point.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int y = point.y - 1;

    // Make the move
    // game->board[y][x].piece = EMPTY;
    game->board[y][x] = EMPTY;

    // Toggle the player related info
    togglePlayer(game);
}

void makeMove(GameState* game, Move move) {
    // Convert the x coordinates from A-H to 0-7
    int oldX = move.start.x - 'A';
    int newXIndex = move.end.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int oldY = move.start.y - 1;
    int newYIndex = move.end.y - 1;

    // Make the move
    // game->board[newYIndex][newXIndex] = game->board[oldY][oldX];
    // game->board[oldY][oldX].piece = EMPTY;
    // game->board[(oldY + newYIndex) / 2][(oldX + newXIndex) / 2].piece = EMPTY;
    game->board[newYIndex][newXIndex] = game->board[oldY][oldX];
    game->board[oldY][oldX] = EMPTY;
    game->board[(oldY + newYIndex) / 2][(oldX + newXIndex) / 2] = EMPTY;

    // Toggle the player related info
    togglePlayer(game);
}

ValidMoves findValidMoves(GameState* game) {
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
    for (int y = 8; y > 0; y--) {
        for (int x = 0; x < 8; x++) {
            // Check if the piece can move to the left
            Move moveLeft = {{'A' + x, y}, {'A' + x - 2, y}};
            if (isValidMove(game, moveLeft) == 1) {
                addValidMove(&validMoves, moveLeft);
                index++;
            }

            // Check if the piece can move to the right
            Move moveRight = {{'A' + x, y}, {'A' + x + 2, y}};
            if (isValidMove(game, moveRight) == 1) {
                addValidMove(&validMoves, moveRight);
                index++;
            }

            // Check if the piece can move up
            Move moveUp = {{'A' + x, y}, {'A' + x, y - 2}};
            if (isValidMove(game, moveUp) == 1) {
                addValidMove(&validMoves, moveUp);
                index++;
            }

            // Check if the piece can move down
            Move moveDown = {{'A' + x, y}, {'A' + x, y + 2}};
            if (isValidMove(game, moveDown) == 1) {
                addValidMove(&validMoves, moveDown);
                index++;
            }
        }
    }

    // Return valid moves array
    return validMoves;
}

void freeValidMoves(ValidMoves* validMoves) {
    free(validMoves->moves);
    validMoves->moves = NULL;
    validMoves->size = 0;
    validMoves->capacity = 0;
}

void addChild(Node* node, Move move) {
    // If the children array is full, double the capacity
    if (node->size == node->capacity) {
        node->capacity *= 2;
        node->children = realloc(node->children, node->capacity * sizeof(Node*));

        // Check if memory allocation failed or not
        if (node->children == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    // Allocate memory for the child
    Node* child = malloc(sizeof(Node));

    // Check if memory allocation failed or not
    if (child == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize the child by copying the parent's game state
    child->game = *copyGameState(&node->game);

    // Make the move on the child's game state
    makeMove(&child->game, move);

    // Add the current move to the previous move of the child
    child->game.prevMove = move;

    // Add the child to the children array
    node->children[node->size] = child;
    node->size++;
}

void generateChildren(Node* node) {
    // Check if it's the first move
    if (node->game.firstMove == 1) {
        // Find valid first moves
        for (int y = 8; y > 0; y--) {
            for (int x = 0; x < 8; x++) {
                Move move = {{'A' + x, y}, {'A' + x, y}};
                if (isValidFirstMove(&node->game, move.start) == 1) {
                    move.end.x = move.start.x;
                    move.end.y = move.start.y;
                    // printf("First Move Child added: %c%d-%c%d\n", move.start.x, move.start.y, move.end.x, move.end.y);
                    addChild(node, move);
                }
            }
        }
        return;
    } else {
        // Find valid moves
        for (int y = 8; y > 0; y--) {
            for (int x = 0; x < 8; x++) {
                // Check if the piece can move to the left
                Move moveLeft = {{'A' + x, y}, {'A' + x + 2, y}};
                if (isValidMove(&node->game, moveLeft) == 1) {
                    // printf("Move Left Child added: %c%d-%c%d\n", moveLeft.start.x, moveLeft.start.y, moveLeft.end.x, moveLeft.end.y);
                    addChild(node, moveLeft);
                }

                // Check if the piece can move to the right
                Move moveRight = {{'A' + x, y}, {'A' + x - 2, y}};
                if (isValidMove(&node->game, moveRight) == 1) {
                    // printf("Move Right Child added: %c%d-%c%d\n", moveRight.start.x, moveRight.start.y, moveRight.end.x, moveRight.end.y);
                    addChild(node, moveRight);
                }

                // Check if the piece can move up
                Move moveUp = {{'A' + x, y}, {'A' + x, y + 2}};
                if (isValidMove(&node->game, moveUp) == 1) {
                    // printf("Move Up Child added: %c%d-%c%d\n", moveUp.start.x, moveUp.start.y, moveUp.end.x, moveUp.end.y);
                    addChild(node, moveUp);
                }

                // Check if the piece can move down
                Move moveDown = {{'A' + x, y}, {'A' + x, y - 2}};
                if (isValidMove(&node->game, moveDown) == 1) {
                    // printf("Move Down Child added: %c%d-%c%d\n", moveDown.start.x, moveDown.start.y, moveDown.end.x, moveDown.end.y);
                    addChild(node, moveDown);
                }
            }
        }
    }
}
