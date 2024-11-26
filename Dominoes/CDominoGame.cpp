// CDominoGame.cpp
#include "CDominoGame.h"
#include <iostream>

CDominoGame::CDominoGame() : gameRunning(true), player1Turn(true) {
    CDominoes deck;

    // Deal dominoes to players
    for (int i = 0; i < 7; ++i) {
        player1.addDomino(deck.dominoes.back());
        deck.dominoes.pop_back();
        player2.addDomino(deck.dominoes.back());
        deck.dominoes.pop_back();
    }
}

void CDominoGame::startGame() {
    while (gameRunning) {
        if (player1Turn) {
            playerTurn(player1, true); // Player 1's turn
        }
        else {
            playerTurn(player2, false); // Player 2's turn
        }
        player1Turn = !player1Turn; // Toggle between players after each turn
    }
}

void CDominoGame::playerTurn(CPlayer& player, bool isPlayer1) {
    std::lock_guard<std::mutex> lock(mtx);

    std::cout << (isPlayer1 ? "Player 1's turn:" : "Player 2's turn:") << std::endl;
    player.displayHand();
    table.display();

    int choice;
    std::cout << "Select domino to play (1-" << player.hand.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > player.hand.size()) {
        std::cout << "Invalid choice. Try again." << std::endl;
        return;  // Return to allow the player to choose again
    }

    auto domino = player.playDomino(choice - 1);

    // If the board is empty, allow the first domino to be placed freely
    if (table.leftValue() == -1 && table.rightValue() == -1) {
        table.addDomino(domino);  // Place the first domino on the board
        std::cout << "First domino placed: [" << domino.first << "|" << domino.second << "]" << std::endl;
    }
    else {
        // Check if the domino can be placed at either end
        bool canPlace = false;
        if (domino.first == table.leftValue() || domino.second == table.leftValue()) {
            // Place the domino on the left end
            table.addDomino(domino);
            canPlace = true;
            std::cout << "Domino placed at left: [" << domino.first << "|" << domino.second << "]" << std::endl;
        }
        else if (domino.first == table.rightValue() || domino.second == table.rightValue()) {
            // Place the domino on the right end
            table.addDomino(domino);
            canPlace = true;
            std::cout << "Domino placed at right: [" << domino.first << "|" << domino.second << "]" << std::endl;
        }

        if (!canPlace) {
            std::cout << "Cannot place this domino. Try again." << std::endl;
            return;  // Return if the domino can't be placed
        }
    }

    // Optional: Check if game is over (you can implement end condition logic)
    // For now, the game continues unless you add some logic to stop it.

    std::cout << (isPlayer1 ? "Player 1's turn over" : "Player 2's turn over") << std::endl;
}
