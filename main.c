#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "game_logic.h"

int main() {
    int boardSize;
    int startX, startY, endX, endY;
    char command;
    char gameMode;
    Stack undoStack = {NULL};
    Stack redoStack = {NULL};
    Board* board = NULL;

    printf("Enter the size of the board (max %d) or 'l' to load a saved game: ", MAX_SIZE);
    if (scanf("%d", &boardSize) == 1) {
        board = createBoard(boardSize);
        if (!board) {
            return 1; // Exit if board creation failed
        }
        initializeBoard(board);
    } else {
        // Clear the invalid input
        while (getchar() != '\n');

        // Load the game
        char filename[100];
        printf("Enter the filename to load the game: ");
        scanf("%s", filename);
        board = loadGame(filename);
        if (!board) {
            return 1; // Exit if loading failed
        }
    }

    printf("Select game mode: (1) Two players, (2) Against computer: ");
    scanf(" %c", &gameMode);

    displayBoard(board);

    while (1) {
        printf("Enter move (m), undo (u), redo (r), save (s), load (l), or quit (q): ");
        scanf(" %c", &command);

        if (command == 'm') {
            if (gameMode == '2') {
                // Player's turn
                printf("Enter the coordinates of the piece to move (col row): ");
                scanf("%d %d", &startX, &startY);
                printf("Enter the coordinates of the target cell (col row): ");
                scanf("%d %d", &endX, &endY);

                // Save the current state to the undo stack before making a move
                push(&undoStack, board);

                makeMove(board, startX, startY, endX, endY);

                // Clear the redo stack since redo is only valid immediately after an undo
                while (redoStack.top != NULL) {
                    Board* temp = pop(&redoStack);
                    freeBoard(temp);
                }

                displayBoard(board);

                if (checkGameEnd(board)) {
                    printf("Game over!\n");
                    break;
                }

                // Computer's turn
                computerMove(board);

                displayBoard(board);

                if (checkGameEnd(board)) {
                    printf("Game over!\n");
                    break;
                }

            } else {
                // Two player mode
                printf("Enter the coordinates of the piece to move (col row): ");
                scanf("%d %d", &startX, &startY);
                printf("Enter the coordinates of the target cell (col row): ");
                scanf("%d %d", &endX, &endY);

                // Save the current state to the undo stack before making a move
                push(&undoStack, board);

                makeMove(board, startX, startY, endX, endY);

                // Clear the redo stack since redo is only valid immediately after an undo
                while (redoStack.top != NULL) {
                    Board* temp = pop(&redoStack);
                    freeBoard(temp);
                }

                displayBoard(board);

                if (checkGameEnd(board)) {
                    printf("Game over!\n");
                    break;
                }
            }
        } else if (command == 'u') {
            undo(&undoStack, &redoStack, &board);
        } else if (command == 'r') {
            redo(&redoStack, &undoStack, &board);
        } else if (command == 's') {
            char filename[100];
            printf("Enter the filename to save the game: ");
            scanf("%s", filename);
            saveGame(board, filename);
        } else if (command == 'l') {
            char filename[100];
            printf("Enter the filename to load the game: ");
            scanf("%s", filename);
            Board* loadedBoard = loadGame(filename);
            if (loadedBoard) {
                freeBoard(board);
                board = loadedBoard;
                displayBoard(board);
            }
        } else if (command == 'q') {
            break;
        }

        displayBoard(board);
    }

    freeBoard(board);

    // Free any remaining board states in the stacks
    while (undoStack.top != NULL) {
        Board* temp = pop(&undoStack);
        freeBoard(temp);
    }
    while (redoStack.top != NULL) {
        Board* temp = pop(&redoStack);
        freeBoard(temp);
    }

    return 0;
}
