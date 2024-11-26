Domino Game Project Documentation
Project Overview
This project implements a console-based domino game in C++. The game simulates a two-player experience with features such as random deck shuffling, turn-based gameplay, the ability to draw from a stack, and a win condition when a player runs out of dominoes. The project showcases core C++ concepts such as classes, vectors, multithreading (mutexes), and input validation.

Features
Random Turn Start

The player who starts is selected randomly using the CRandom class.
The deck is shuffled at the beginning to ensure a fair distribution of dominoes.
Turn-Based Gameplay

Players alternate turns.
A player can either play a valid domino or draw from the stack if they cannot play.
Win Condition

The game ends when a player runs out of dominoes.
The winner is announced, along with a summary of the remaining dominoes and the dominoes placed on the table.
Visual Display

Remaining dominoes for each player and the stack are displayed visually.
Dominoes placed on the table are shown using the CTable::display method.
Steps Taken in Implementation
1. Initial Setup
Classes Created:

CDominoGame: Manages game logic and player interactions.
CPlayer: Represents a player with a hand of dominoes.
CTable: Represents the game table and manages placed dominoes.
CRandom: Used to shuffle the deck and determine the starting player.
Deck Initialization:

A full set of dominoes (pairs of numbers from 0 to 6) is generated and shuffled using the CRandom::shuffle method.
2. Game Mechanics
Player Turns:

Players select a domino to play by entering its index.
If the selected domino cannot be placed, the player draws from the stack.
If the stack is empty, the player skips their turn.
Domino Placement Rules:

A domino can only be placed if its number matches the current left or right value of the table.
The first domino can be placed freely.
3. End-Game Conditions
Win Detection:

The game checks after every turn if a player's hand is empty.
If so, the game ends, and the winner is announced.
Summary Display:

Remaining dominoes in each player’s hand and the stack are displayed.
Total dominoes placed on the table are shown visually using CTable::display.
4. Additional Features
Input Validation:

Ensures players only select valid domino indices or valid options for drawing.
Multithreading for Safety:

Mutexes (std::mutex) are used to ensure thread safety for shared resources such as the game table.
How to Run
Clone the repository or download the source code.
Compile the project using a C++ compiler (e.g., g++):
bash
Copy code
g++ CDominoGame.cpp CPlayer.cpp CTable.cpp CRandom.cpp main.cpp -o DominoGame

Run the compiled executable:

Follow the on-screen instructions to play the game.
Code Files

CDominoGame.cpp:
Implements the game logic and handles player turns.

CPlayer.cpp:
Manages the player's hand and interactions with the game.

CTable.cpp:
Manages the game board and domino placement.

CRandom.cpp:
Provides utility functions for shuffling the deck and random number generation.

main.cpp:
Entry point of the program.

Future Improvements
AI Implementation:
Add AI logic for single-player mode against a computer opponent.

Graphical User Interface (GUI):
Upgrade the console-based game to a graphical interface for better user experience.

Game Modes:
Introduce new game modes, such as multiplayer with more players or variations of domino rules.

Statistics Tracking:
Record and display player statistics, such as wins and draws.

Acknowledgments
Developed by Owen N Chilson.
