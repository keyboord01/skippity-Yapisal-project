#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_logic.h"

// Function to check if a move is valid
int isValidMove(Board* board, int startX, int startY, int endX, int endY) {
    // Check if start and end positions are within board boundaries
    if (startX < 0 || startX >= board->size || startY < 0 || startY >= board->size ||
        endX < 0 || endX >= board->size || endY < 0 || endY >= board->size) {
        return 0;
    }

    // Check if start position has a piece and end position is empty
    if (!board->cells[startX][startY].isOccupied || board->cells[endX][endY].isOccupied) {
        return 0;
    }

    // Check if the move is in a straight line and skips at least one cell
    if (startX != endX && startY != endY) {
        return 0;
    }
    if (abs(startX - endX) <= 1 && abs(startY - endY) <= 1) {
        return 0;
    }

    // Check if there are pieces to capture in the path
    int dx = (endX - startX) ? (endX - startX) / abs(endX - startX) : 0;
    int dy = (endY - startY) ? (endY - startY) / abs(endY - startY) : 0;
    int x = startX + dx, y = startY + dy;

    int hasCapture = 0;
    while (x != endX || y != endY) {
        if (board->cells[x][y].isOccupied) {
            hasCapture = 1;
            break;
        }
        x += dx;
        y += dy;
    }
    return hasCapture;
}

// Function to make a move and capture pieces
void makeMove(Board* board, int startX, int startY, int endX, int endY) {
    if (isValidMove(board, startX, startY, endX, endY)) {
        int dx = (endX - startX) ? (endX - startX) / abs(endX - startX) : 0;
        int dy = (endY - startY) ? (endY - startY) / abs(endY - startY) : 0;
        int x = startX + dx, y = startY + dy;

        // Capture pieces in the path
        while (x != endX || y != endY) {
            if (board->cells[x][y].isOccupied) {
                board->cells[x][y].piece = ' ';
                board->cells[x][y].isOccupied = 0;
                if (board->cells[startX][startY].piece == 'P') {
                    board->playerScore++;
                } else if (board->cells[startX][startY].piece == 'C') {
                    board->computerScore++;
                }
            }
            x += dx;
            y += dy;
        }

        // Move the piece
        board->cells[endX][endY].piece = board->cells[startX][startY].piece;
        board->cells[endX][endY].isOccupied = 1;
        board->cells[startX][startY].piece = ' ';
        board->cells[startX][startY].isOccupied = 0;

        // Allow multiple jumps
        while (1) {
            displayBoard(board);
            printf("Do you want to make another jump with the same piece? (y/n): ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'n') {
                break;
            }
            printf("Enter the coordinates of the target cell for the next jump (row col): ");
            scanf("%d %d", &endX, &endY);

            if (!isValidMove(board, startX, startY, endX, endY)) {
                printf("Invalid move! Ending turn.\n");
                break;
            }

            // Capture pieces in the new path
            dx = (endX - startX) ? (endX - startX) / abs(endX - startX) : 0;
            dy = (endY - startY) ? (endY - startY) / abs(endY - startY) : 0;
            x = startX + dx;
            y = startY + dy;

            while (x != endX || y != endY) {
                if (board->cells[x][y].isOccupied) {
                    board->cells[x][y].piece = ' ';
                    board->cells[x][y].isOccupied = 0;
                    if (board->cells[startX][startY].piece == 'P') {
                        board->playerScore++;
                    } else if (board->cells[startX][startY].piece == 'C') {
                        board->computerScore++;
                    }
                }
                x += dx;
                y += dy;
            }

            // Move the piece
            board->cells[endX][endY].piece = board->cells[startX][startY].piece;
            board->cells[endX][endY].isOccupied = 1;
            board->cells[startX][startY].piece = ' ';
            board->cells[startX][startY].isOccupied = 0;

            // Update the start coordinates for the next potential jump
            startX = endX;
            startY = endY;
        }

        // Update board after the move
        updateBoard(board, startX, startY, endX, endY);
    } else {
        printf("Invalid move! Please try again.\n");
    }
}

// Function to update the board after a move
void updateBoard(Board* board, int startX, int startY, int endX, int endY) {
    // For now, just print the updated board
    displayBoard(board);
}

// Function to check if there are any valid moves left
int hasValidMoves(Board* board) {
    for (int startX = 0; startX < board->size; startX++) {
        for (int startY = 0; startY < board->size; startY++) {
            if (board->cells[startX][startY].isOccupied) {
                for (int endX = 0; endX < board->size; endX++) {
                    for (int endY = 0; endY < board->size; endY++) {
                        if (isValidMove(board, startX, startY, endX, endY)) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// Function to check if the game has ended
int checkGameEnd(Board* board) {
    int playerPieces = 0;
    int computerPieces = 0;

    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (board->cells[i][j].isOccupied) {
                if (board->cells[i][j].piece == 'P') {
                    playerPieces++;
                } else if (board->cells[i][j].piece == 'C') {
                    computerPieces++;
                }
            }
        }
    }

    if (playerPieces == 0 || computerPieces == 0 || !hasValidMoves(board)) {
        return 1;
    }
    return 0;
}

// Function to create a copy of the board
Board* copyBoard(Board* board) {
    Board* newBoard = createBoard(board->size);
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            newBoard->cells[i][j].piece = board->cells[i][j].piece;
            newBoard->cells[i][j].isOccupied = board->cells[i][j].isOccupied;
        }
    }
    return newBoard;
}

// Function to push a board state onto the stack
void push(Stack* stack, Board* board) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->boardState = copyBoard(board);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a board state from the stack
Board* pop(Stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    Board* boardState = temp->boardState;
    free(temp);
    return boardState;
}

// Function to undo a move
void undo(Stack* undoStack, Stack* redoStack, Board** board) {
    if (undoStack->top == NULL) {
        printf("No moves to undo!\n");
        return;
    }
    push(redoStack, *board);
    *board = pop(undoStack);
    displayBoard(*board);
}

// Function to redo a move
void redo(Stack* redoStack, Stack* undoStack, Board** board) {
    if (redoStack->top == NULL) {
        printf("No moves to redo!\n");
        return;
    }
    push(undoStack, *board);
    *board = pop(redoStack);
    displayBoard(*board);
}

// Function to save the game state to a file
void saveGame(Board* board, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Failed to open file for saving.\n");
        return;
    }
    fwrite(&board->size, sizeof(int), 1, file);
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            fwrite(&board->cells[i][j].piece, sizeof(char), 1, file);
            fwrite(&board->cells[i][j].isOccupied, sizeof(int), 1, file);
        }
    }
    fwrite(&board->playerScore, sizeof(int), 1, file);
    fwrite(&board->computerScore, sizeof(int), 1, file);
    fclose(file);
    printf("Game saved successfully.\n");
}

// Function to load the game state from a file
Board* loadGame(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file for loading.\n");
        return NULL;
    }
    int size;
    fread(&size, sizeof(int), 1, file);
    Board* board = createBoard(size);
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            fread(&board->cells[i][j].piece, sizeof(char), 1, file);
            fread(&board->cells[i][j].isOccupied, sizeof(int), 1, file);
        }
    }
    fread(&board->playerScore, sizeof(int), 1, file);
    fread(&board->computerScore, sizeof(int), 1, file);
    fclose(file);
    printf("Game loaded successfully.\n");
    return board;
}

// Helper function to count the number of captures for a move
int countCaptures(Board* board, int startX, int startY, int endX, int endY) {
    int captures = 0;
    int dx = (endX - startX) ? (endX - startX) / abs(endX - startX) : 0;
    int dy = (endY - startY) ? (endY - startY) / abs(endY - startY) : 0;
    int x = startX + dx, y = startY + dy;

    while (x != endX || y != endY) {
        if (board->cells[x][y].isOccupied) {
            captures++;
        }
        x += dx;
        y += dy;
    }

    return captures;
}

// Function for the computer to make a move
void computerMove(Board* board) {
    int bestStartX, bestStartY, bestEndX, bestEndY;
    int maxCaptures = -1;
    srand(time(NULL));

    // Iterate over all possible moves and choose the one with the most captures
    for (int startX = 0; startX < board->size; startX++) {
        for (int startY = 0; startY < board->size; startY++) {
            if (board->cells[startX][startY].isOccupied) {
                for (int endX = 0; endX < board->size; endX++) {
                    for (int endY = 0; endY < board->size; endY++) {
                        if (isValidMove(board, startX, startY, endX, endY)) {
                            int captures = countCaptures(board, startX, startY, endX, endY);
                            if (captures > maxCaptures) {
                                bestStartX = startX;
                                bestStartY = startY;
                                bestEndX = endX;
                                bestEndY = endY;
                                maxCaptures = captures;
                            }
                        }
                    }
                }
            }
        }
    }

    if (maxCaptures > 0) {
        makeMove(board, bestStartX, bestStartY, bestEndX, bestEndY);
        printf("Computer moved from (%d, %d) to (%d, %d)\n", bestStartX, bestStartY, bestEndX, bestEndY);
    } else {
        // No valid move found, choose a random move
        int startX, startY, endX, endY;
        while (1) {
            startX = rand() % board->size;
            startY = rand() % board->size;
            endX = rand() % board->size;
            endY = rand() % board->size;

            if (isValidMove(board, startX, startY, endX, endY)) {
                makeMove(board, startX, startY, endX, endY);
                printf("Computer moved from (%d, %d) to (%d, %d)\n", startX, startY, endX, endY);
                break;
            }
        }
    }
}
