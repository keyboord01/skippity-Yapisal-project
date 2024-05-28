#ifndef BOARD_H
#define BOARD_H

#define MAX_SIZE 20

// Structure to represent a cell on the board
typedef struct {
    char piece;
    int isOccupied;
} Cell;

// Structure to represent the board
typedef struct {
    int size;
    Cell** cells;
    int playerScore;
    int computerScore;
} Board;

// Function declarations
Board* createBoard(int size);
void initializeBoard(Board* board);
void placePieces(Board* board);
void displayBoard(Board* board);
void freeBoard(Board* board);

#endif // BOARD_H
