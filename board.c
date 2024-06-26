#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

// Function to create a new board 
Board* createBoard(int size) {
    if (size > MAX_SIZE) {
        printf("Board size too large! Maximum size is %d.\n", MAX_SIZE);
        return NULL;
    }

    Board* board = (Board*)malloc(sizeof(Board));
    if (!board) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    board->size = size;
    board->playerScore = 0;
    board->computerScore = 0;
    board->cells = (Cell**)malloc(size * sizeof(Cell*));
    if (!board->cells) {
        printf("Memory allocation failed!\n");
        free(board);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        board->cells[i] = (Cell*)malloc(size * sizeof(Cell));
        if (!board->cells[i]) {
            printf("Memory allocation failed!\n");
            for (int j = 0; j < i; j++) {
                free(board->cells[j]);
            }
            free(board->cells);
            free(board);
            return NULL;
        }
    }

    initializeBoard(board);
    return board;
}

// Function to initialize the board with empty cells
void initializeBoard(Board* board) {
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            board->cells[i][j].piece = ' ';
            board->cells[i][j].isOccupied = 0;
        }
    }

    placePieces(board);
}

// Function to randomly place pieces on the board, leaving the center empty
void placePieces(Board* board) {
    char pieces[] = {'A', 'B', 'C'};
    int numPieces = sizeof(pieces) / sizeof(pieces[0]);
    int center = board->size / 2;

    srand(time(NULL));

    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            // Skip the center 2x2 squares
            if ((i == center || i == center - 1) && (j == center || j == center - 1)) {
                continue;
            }

            if (!board->cells[i][j].isOccupied) {
                board->cells[i][j].piece = pieces[rand() % numPieces];
                board->cells[i][j].isOccupied = 1;
            }
        }
    }
}

// Function to display the board
void displayBoard(Board* board) {
    printf("   ");
    for (int i = 0; i < board->size; i++) {
        printf(" %2d ", i);
    }
    printf("\n");

    for (int i = 0; i < board->size; i++) {
        printf("%2d ", i);

        for (int j = 0; j < board->size; j++) {
            if (board->cells[i][j].isOccupied) {
                printf("| %c ", board->cells[i][j].piece);
            } else {
                printf("|   ");
            }
        }
        printf("|\n");

        printf("   ");
        for (int j = 0; j < board->size; j++) {
            printf("----");
        }
        printf("-\n");
    }

    printf("Player Score: %d\n", board->playerScore);
    printf("Computer Score: %d\n", board->computerScore);
}



// Function to free the memory allocated for the board
void freeBoard(Board* board) {
    for (int i = 0; i < board->size; i++) {
        free(board->cells[i]);
    }
    free(board->cells);
    free(board);
}
