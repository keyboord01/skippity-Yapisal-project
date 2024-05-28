#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "board.h"

// Structure to represent a stack node
typedef struct StackNode {
    Board* boardState;
    struct StackNode* next;
} StackNode;

// Stack structure to keep track of board states for undo/redo
typedef struct {
    StackNode* top;
} Stack;

// Function declarations
int isValidMove(Board* board, int startX, int startY, int endX, int endY);
void makeMove(Board* board, int startX, int startY, int endX, int endY);
void updateBoard(Board* board, int startX, int startY, int endX, int endY);
void push(Stack* stack, Board* board);
Board* pop(Stack* stack);
void undo(Stack* undoStack, Stack* redoStack, Board** board);
void redo(Stack* redoStack, Stack* undoStack, Board** board);
Board* copyBoard(Board* board);
void saveGame(Board* board, const char* filename);
Board* loadGame(const char* filename);

// Computer opponent functions
void computerMove(Board* board);

#endif // GAME_LOGIC_H
