#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "minimaxAgent.h"


int whoseTurn(GameState* game) {
    int black = 0;
    int white = 0;

    for (int y = 8; y > 0; y--) {
        for (int x = 0; x < 8; x++) {
            if (game->board[y-1][x].piece == 'B') {
                black++;
            }
            else if (game->board[y-1][x].piece == 'W') {
                white++;
            }
        }
    }

    if (black == white) {
        return MAXIMIZING_PLAYER;
    }
    else {
        return MINIMIZING_PLAYER;
    }
}

GameState* initalizeGame(char* game) {
    // Allocate memory for the new game
    GameState* newGame = malloc(sizeof(GameState));

    // Check if memory allocation failed or not
    if (newGame == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize the game board
    for (int y = 8; y > 0; y--) {
        for (int x = 0; x < 8; x++) {
            newGame->board[y-1][x].piece = game[(8-y)*8 + x];
            newGame->board[y-1][x].position.x = x;
            newGame->board[y-1][x].position.y = y;
        }
    }

    // Determine the player's turn
    int player = whoseTurn(newGame);

    // Set the correct player
    newGame->player = player;

    // Set the winner to empty
    newGame->winner = EMPTY;

    // Return the new game
    return newGame;
}

void agentOutput(Move move) {
	// If the start and end coordinates are the same, then it's a first move
	if (move.start.x == move.end.x && move.start.y == move.end.y) {
		printf("%c%d", move.start.x, move.start.y);
	}

	// Otherwise, it's a regular move
	else {
		printf("%c%d-%c%d", move.start.x, move.start.y, move.end.x, move.end.y);
	}
}

int main() {

}
