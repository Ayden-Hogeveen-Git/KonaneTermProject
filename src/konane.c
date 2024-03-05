#include <stdlib.h>
#include <stdio.h>
#include "structures.h"


const char* directionToString(Direction direction) {
    switch (direction) {
        case LEFT: return "LEFT";
        case RIGHT: return "RIGHT";
        case UP: return "UP";
        case DOWN: return "DOWN";
        case FIRST: return "FIRST";
        default:
            return "INVALID";
    }
}

const int directionToInt(Direction direction) {
    switch (direction) {
        case LEFT: return -1;
        case RIGHT: return 1;
        case UP: return 1;
        case DOWN: return -1;
        case FIRST: return 0;
        default:
            return 0;
    }
}

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

char* gameStateToString(GameState* game) {
    // Allocate memory for the game string
    char* gameString = malloc(65 * sizeof(char));

    // Check if memory allocation failed or not
    if (gameString == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    // Copy the game board to the game string
    int index = 0;
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x <= 7; x++) {
            gameString[index] = pieceToChar(game->board[y][x]);
            index++;
        }
    }

    // Add the null terminator to the end of the game string
    gameString[64] = '\0';

    // Return the game string
    return gameString;
}

void initializeBoard(GameState* game) {
    // Initialize the game board
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x <= 7; x++) {
            game->board[y][x] = (y + x) % 2 == 0 ? BLACK : WHITE;
        }
    }

}

GameState* initializeGameState() {
    // Allocate memory for the game
    GameState* game = malloc(sizeof(GameState));

    // Check if memory allocation failed or not
    if (game == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
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
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    // Copy the game board state
    for (int y = 7; y <= 0; y++) {
        for (int x = 0; x <= 7; x++) {
            newGame->board[y][x] = game->board[y][x];
        }
    }

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

int isValidMove(GameState* game, Player player, Move move) {
    // Convert the x coordinates from A-H to 0-7
    int x = move.start.x - 'A';
    int newX = move.end.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int y = move.start.y - 1;
    int newY = move.end.y - 1;

    // Check if it's the first move or not
    if (game->firstMove == 1 && move.jumps == 0) {
        // Verify that the start coordinates are within the board starting area
        if (x < 3 || x > 4 || y < 3 || y > 4) {
            return 0;
        }

        // Verify that the player is removing their own piece
        if (player == BLACK && game->board[y][x] != BLACK) {
            return 0;
        } else if (player == WHITE && game->board[y][x] != WHITE) {
            return 0;
        }

        return 1;
    } else {
        // Verify that the start coordinates are within the game board
        if (x < 0 || x > 7 || y < 0 || y > 7) {
            return 0;
        }

        // Verify that the end coordinates are within the game board
        if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
            return 0;
        }

        // Verify that the piece is moving to an empty space
        if (game->board[newY][newX] != EMPTY) {
            return 0;
        }

        // Verify that the piece is moving in a straight line
        if (newY != y && newX != x) {
            return 0;
        }

        // Verify that the player is moving their own piece
        if (player == BLACK && game->board[y][x] != BLACK) {
            return 0;
        } else if (player == WHITE && game->board[y][x] != WHITE) {
            return 0;
        }

        // Initialize the x and y index for validating the jumped pieces
        int xIndex, yIndex;

        // Handle single jump validation
        if (move.jumps == 1) {
            xIndex = (x + newX) / 2;
            yIndex = (y + newY) / 2;

            // Verify that the player is jumping over an opponent's piece
            if (player == BLACK && game->board[yIndex][xIndex] != WHITE) {
                return 0;
            } else if (player == WHITE && game->board[yIndex][xIndex] != BLACK) {
                return 0;
            }
        }

        // Handle double jump validation
        if (move.jumps == 2) {
            return 0;
        }

        // Handle triple jump validation
        if (move.jumps == 3) {
            return 0;
        }

        // Verify that the player is jumping over an opponent's piece
        // for (int i = 1; i <= move.jumps; i++) {
        // 	if (move.direction == LEFT) {
        // 		int yIndex = (y + newY) / 2;
        // 		int xIndex = (x + newX) / 2 - (move.jumps - 1);
        // 		if (player == BLACK && game->board[yIndex][xIndex] != WHITE) {
        // 			return 0;
        // 		} else if (player == WHITE && game->board[yIndex][xIndex] != BLACK) {
        // 			return 0;
        // 		}
                
        // 	} else if (move.direction == RIGHT) {
        // 		int yIndex = (y + newY) / 2;
        // 		int xIndex = (x + newX) / 2 + (move.jumps - 1);
        // 		if (player == BLACK && game->board[yIndex][xIndex] != WHITE) {
        // 			return 0;
        // 		} else if (player == WHITE && game->board[yIndex][xIndex] != BLACK) {
        // 			return 0;
        // 		}
        // 	} else if (move.direction == UP) {
        // 		int yIndex = (y + newY) / 2 + (move.jumps - 1);
        // 		int xIndex = (x + newX) / 2;
        // 		if (player == BLACK && game->board[yIndex][xIndex] != WHITE) {
        // 			return 0;
        // 		} else if (player == WHITE && game->board[yIndex][xIndex] != BLACK) {
        // 			return 0;
        // 		}
        // 	} else if (move.direction == DOWN) {
        // 		int yIndex = (y + newY) / 2 - (move.jumps - 1);
        // 		int xIndex = (x + newX) / 2;
        // 		if (player == BLACK && game->board[yIndex][xIndex] != WHITE) {
        // 			return 0;
        // 		} else if (player == WHITE && game->board[yIndex][xIndex] != BLACK) {
        // 			return 0;
        // 		}
        // 	}
        // }
        return 1;
    }
}

int isFirstMove(GameState* game) {
    // Initialize the empty counter
    int emptyCounter = 0;

    // Count the number of empty spaces, if there are less than 2, then it's the first move
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x <= 7; x++) {
            if (game->board[y][x] == EMPTY) {
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

void makeMove(GameState* game, Move move) {
    // Convert the x coordinates from A-H to 0-7
    int oldX = move.start.x - 'A';
    int newX = move.end.x - 'A';

    // Convert the y coordinates from 1-8 to 0-7
    int oldY = move.start.y - 1;
    int newY = move.end.y - 1;

    // Make the move
    game->board[newY][newX] = game->board[oldY][oldX];
    game->board[oldY][oldX] = EMPTY;

    // Initialize the x and y index for removing the jumped pieces
    int xIndex, yIndex;

    // Handle first move
    if (game->firstMove == 1 && move.jumps == 0) {
        yIndex = oldY;
        xIndex = oldX;

        // Remove the piece at the current position
        if (game->board[yIndex][xIndex] != EMPTY) {
            game->board[yIndex][xIndex] = EMPTY;
        }
    } else {
        // Handle single jumps
        if (move.jumps >= 1) {
            if (move.direction == LEFT || move.direction == RIGHT) {
                xIndex = oldX + (1 * directionToInt(move.direction));
                yIndex = oldY;
            } else if (move.direction == UP || move.direction == DOWN) {
                xIndex = oldX;
                yIndex = oldY + (1 * directionToInt(move.direction));
            } else {
                fprintf(stderr, "Error: Invalid move direction\n");
                exit(1);
            }

            // Remove the piece at the current position
            if (game->board[yIndex][xIndex] != EMPTY) {
                game->board[yIndex][xIndex] = EMPTY;
            }
        }

        // Handle double jumps
        if (move.jumps >= 2) {
            int xIndex, yIndex;
            if (move.direction == LEFT || move.direction == RIGHT) {
                xIndex = oldX + (3 * directionToInt(move.direction));
                yIndex = oldY;
            } else if (move.direction == UP || move.direction == DOWN) {
                xIndex = oldX;
                yIndex = oldY + (3 * directionToInt(move.direction));
            } else {
                fprintf(stderr, "Error: Invalid move direction\n");
                exit(1);
            }

            // Remove the piece at the current position
            if (game->board[yIndex][xIndex] != EMPTY) {
                game->board[yIndex][xIndex] = EMPTY;
            }
        }

        // Handle triple jumps
        if (move.jumps >= 3) {
            int xIndex, yIndex;
            if (move.direction == LEFT || move.direction == RIGHT) {
                xIndex = oldX + (5 * directionToInt(move.direction));
                yIndex = oldY;
            } else if (move.direction == UP || move.direction == DOWN) {
                xIndex = oldX;
                yIndex = oldY + (5 * directionToInt(move.direction));
            } else {
                fprintf(stderr, "Error: Invalid move direction\n");
                exit(1);
            }

            // Remove the piece at the current position
            if (game->board[yIndex][xIndex] != EMPTY) {
                game->board[yIndex][xIndex] = EMPTY;
            }
        }
    }

    // Toggle the player related info
    togglePlayer(game);
}

Move getLeftMove(int jumps, int x, int y) {
	Move moveLeft;

    // Set the direction and number of jumps
    moveLeft.direction = LEFT;
    moveLeft.jumps = jumps;

    // Set the start and end coordinates for the move
    moveLeft.start.x = 'A' + x;
    moveLeft.end.x = 'A' + x + (2 * jumps * directionToInt(moveLeft.direction));
    moveLeft.start.y = y + 1;
    moveLeft.end.y = y + 1;

	return moveLeft;
}

Move getRightMove(int jumps, int x, int y) {
    Move moveRight;

    // Set the direction and number of jumps
    moveRight.direction = RIGHT;
    moveRight.jumps = jumps;

    // Set the start and end coordinates for the move
    moveRight.start.x = 'A' + x;
    moveRight.end.x = 'A' + x + (2 * jumps * directionToInt(moveRight.direction));
    moveRight.start.y = y + 1;
    moveRight.end.y = y + 1;
    
    return moveRight;
}

Move getUpMove(int jumps, int x, int y) {
	Move moveUp;

    // Set the direction and number of jumps
    moveUp.direction = UP;
    moveUp.jumps = jumps;

    // Set the start and end coordinates for the move
    moveUp.start.x = 'A' + x;
    moveUp.end.x = 'A' + x;
    moveUp.start.y = y + 1;
    moveUp.end.y = y + 1 + (2 * jumps * directionToInt(moveUp.direction));

    return moveUp;
}

Move getDownMove(int jumps, int x, int y) {
    Move moveDown;

    // Set the direction and number of jumps
    moveDown.direction = DOWN;
    moveDown.jumps = jumps;

    // Set the start and end coordinates for the move
    moveDown.start.x = 'A' + x;
    moveDown.end.x = 'A' + x;
    moveDown.start.y = y + 1;
    moveDown.end.y = y + 1 + (2 * jumps * directionToInt(moveDown.direction));

    return moveDown;
}

int isTerminal(Node* node) {
    // Check if the game is over
    if (node->game.winner != EMPTY) {
        return 1;
    }

    // Check if the game is at the max depth
    if (node->size == 0) {
        return 1;
    }

    return 0;
}

int countValidMoves(GameState* game, Player player) {
    // Count the number of possible moves for the current player
    int counter = 0;

    // Count the number of possible moves for the current player
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x <= 7; x++) {
            // Check if there's a piece at the current position
            if (game->board[y][x] == player) {

                // Check if the piece can move left
                for (int jumps = 1; jumps <= 3; jumps++) {
                    Move moveLeft = getLeftMove(jumps, x, y);
                    if (isValidMove(game, player, moveLeft) == 1) {
                        counter++;
                    } else {
                        break;
                    }
                }

                // Check if the piece can move right
                for (int jumps = 1; jumps <= 3; jumps++) {
                    Move moveRight = getRightMove(jumps, x, y);
                    if (isValidMove(game, player, moveRight) == 1) {
                        counter++;
                    } else {
                        break;
                    }
                }

                // Check if the piece can move up
                for (int jumps = 1; jumps <= 3; jumps++) {
                    Move moveUp = getUpMove(jumps, x, y);
                    if (isValidMove(game, player, moveUp) == 1) {
                        counter++;
                    } else {
                        break;
                    }
                }

                // Check if the piece can move down
                for (int jumps = 1; jumps <= 3; jumps++) {
                    Move moveDown = getDownMove(jumps, x, y);
                    if (isValidMove(game, player, moveDown) == 1) {
                        counter++;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    return counter == 0;
}

void checkForWinner(GameState* game) {
    // No possible winner on first moves
    if (game->firstMove == 1) {
        game->winner = EMPTY;
    } else {
        // Count the number of possible moves for each player
        int blackCounter = countValidMoves(game, BLACK);
        int whiteCounter = countValidMoves(game, WHITE);

        // Check if there's a winner
        if (blackCounter > 0 && whiteCounter == 0) {
            game->winner = BLACK;
        } else if (whiteCounter > 0 && blackCounter == 0) {
            game->winner = WHITE;
        } else if (blackCounter == 0 && whiteCounter == 0 && game->turn == BLACK) {
            game->winner = WHITE;
        } else if (blackCounter == 0 && whiteCounter == 0 && game->turn == WHITE) {
            game->winner = BLACK;
        } else if (whiteCounter == 0 && game->turn == WHITE) {
            game->winner = BLACK;
        } else if (blackCounter == 0 && game->turn == BLACK) {
            game->winner = WHITE;
        } else {
            game->winner = EMPTY;
        }
    }
}

void addChild(Node* node, Move move) {
    // If the children array is full, double the capacity
    if (node->size == node->capacity) {
        node->capacity *= 2;
        node->children = realloc(node->children, node->capacity * sizeof(Node*));

        // Check if memory allocation failed or not
        if (node->children == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1);
        }
    }

    // Allocate memory for the child
    Node* child = malloc(sizeof(Node));

    // Check if memory allocation failed or not
    if (child == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    // Initialize all fields of the child to 0
    *child = (Node) {0};

    // Allocate memory for the children array with a capacity of 10
    child->capacity = 10;
    child->children = malloc(child->capacity * sizeof(Node*));

    // Check if memory allocation failed or not
    if (child->children == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    // Copy the parent's game state
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
    // Generate children for the current node
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x <= 7; x++) {
            // Check if there's a piece at the current position
            if (node->game.board[y][x] == BLACK || node->game.board[y][x] == WHITE) {
                
                // Check if the piece can move left
                for (int jumps = 1; jumps <= 3; jumps++) {
                    Move moveLeft = getLeftMove(jumps, x, y);
                    if (isValidMove(&node->game, node->game.turn, moveLeft) == 1) {
                        addChild(node, moveLeft);
                    } else {
                        break;
                    }
                }

                // Check if the piece can move right
                for (int jumps = 1; jumps <= 3; jumps++) {
                    Move moveRight = getRightMove(jumps, x, y);
                    if (isValidMove(&node->game, node->game.turn, moveRight) == 1) {
                        addChild(node, moveRight);
                    } else {
                        break;
                    }
                }

                // Check if the piece can move up
                for (int jumps = 1; jumps <= 3; jumps++) {
                    Move moveUp = getUpMove(jumps, x, y);
                    if (isValidMove(&node->game, node->game.turn, moveUp) == 1) {
                        addChild(node, moveUp);
                    } else {
                        break;
                    }
                }

                // Check if the piece can move down
                for (int jumps = 1; jumps <= 3; jumps++) {
                    Move moveDown = getDownMove(jumps, x, y);
                    if (isValidMove(&node->game, node->game.turn, moveDown) == 1) {
                        addChild(node, moveDown);
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

void generateTree(Node* node, int depth) {
    // Base case to stop the recursion
    if (depth == 0) {
        return;
    }

    // Generate children for the current node
    generateChildren(node);

    // Generate children for each child
    for (int i = 0; i < node->size; i++) {
        generateTree(node->children[i], depth - 1);
    }
}

void freeTree(Node* node) {
   // Base case: if the node is NULL, there's nothing to free
    if (node == NULL) {
        return;
    }

    // First free all the children of this node
    for (int i = 0; i < node->size; i++) {
        freeTree(node->children[i]);
    }

    // Then free the children array
    free(node->children);

    // Finally free the node itself
    free(node);
}
