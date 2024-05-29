# Skippity-Yapisal-Project

Skippity is a board game I made in C Language as part of a university project. The game allows players to make moves to jump over pieces and capture them. This project is developed in C and includes functionalities such as saving/loading games, undo/redo moves, and playing against the computer.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Setup](#setup)
- [How to Play](#how-to-play)
- [Game Rules](#game-rules)
- [Project Structure](#project-structure)
- [Contributing](#contributing)

## Overview

This project was developed as the project for the structured programming course. The objective of the project is to design and implement a board game in C, focusing on developing a modular and well-structured codebase. The game features dynamic board sizes, a computer opponent, and functionalities for saving/loading game states and undoing/redoing moves.

## Features

- **Dynamic Board Size:** The game board can be of any size up to 20x20.
- **Player and Computer Moves:** Play against another player or the computer.
- **Undo/Redo Moves:** Undo or redo your last move.
- **Save/Load Game:** Save your current game and load it later from the `saved_games` directory.

## Setup

### Prerequisites

- A C compiler (e.g., GCC)

### Compilation

To compile the project, run the following command in your terminal:

```sh
gcc -o skippity main.c board.c game_logic.c
```

## Running the Game

To start the game, run the following command:

```sh
./skippity
```

## How to Play

1. **Start the Game:** Enter the size of the board or load a saved game.
2. **Select Game Mode:** Choose between two players or playing against the computer.
3. **Make Moves:** Enter the coordinates of the piece you want to move and the target cell.
4. **Capture Pieces:** Jump over pieces to capture them.
5. **Undo/Redo:** Use the undo and redo options to reverse moves.
6. **Save/Load Game:** Save the current game state to a file or load a previously saved game.

## Game Rules

- **Objective:** Capture as many pieces as possible.
- **Moves:** Players move by jumping over adjacent pieces to capture them.
- **End of Game:** The game ends when no valid moves are left.

## Project Structure

- **main.c:** Contains the main game loop and user interaction.
- **board.c / board.h:** Manages the game board, including creation, initialization, and display.
- **game_logic.c / game_logic.h:** Implements the game logic, including move validation, capturing pieces, computer moves, saving and loading game states and undo and redo functionality.

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, feel free to create an issue or submit a pull request.

### Fork the Repository

1. Fork the repository on GitHub.
2. Clone your fork:

   ```sh
   git clone https://github.com/your-username/skippity-Yapisal-project.git
   ```

3. Create a new branch:

   ```sh
   git checkout -b feature-branch
   ```

4. Make your changes and commit them:

   ```sh
   git commit -m "Description of your changes"
   ```

5. Push to your fork:

   ```sh
   git push origin feature-branch
   ```

6. Open a pull request on GitHub.
