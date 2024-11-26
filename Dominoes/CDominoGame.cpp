// CDominoGame.cpp
#include "CDominoGame.h"
#include "CRandom.h"
#include <iostream>

CDominoGame::CDominoGame() : gameRunning(true) {
    CDominoes deck;
    CRandom randomGen;

    // Determine the starting player randomly
    player1Turn = randomGen.randomBool();

    // Deal dominoes to players
    for (int i = 0; i < 10; ++i) {
        player1.addDomino(deck.dominoes.back());
        deck.dominoes.pop_back();
        player2.addDomino(deck.dominoes.back());
        deck.dominoes.pop_back();
    }

    remainingDeck = deck.dominoes;
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

    std::cout << std::endl << (isPlayer1 ? "Player 1's turn:" : "Player 2's turn:") << std::endl;
    player.displayHand();
    table.display();

    int choice;
    std::cout << "Select domino to play (1-" << player.hand.size() << " or 0 to draw): ";
    std::cin >> choice;

    // Draw a card if the player chooses 0
    if (choice == 0) {
        if (!remainingDeck.empty()) {
            auto drawnCard = remainingDeck.back();
            remainingDeck.pop_back();
            player.addDomino(drawnCard);
            std::cout << "You drew a domino: [" << drawnCard.first << "|" << drawnCard.second << "]" << std::endl;
        }
        else {
            std::cout << "No more dominoes to draw." << std::endl;
        }
        return;  // End the turn after drawing
    }

    // Validate choice
    if (choice < 1 || choice > player.hand.size()) {
        std::cout << "Invalid choice. Try again." << std::endl;
        return;  // Return to allow the player to choose again
    }

    auto domino = player.playDomino(choice - 1);

    // If the board is empty, allow the first domino to be placed freely
    if (table.leftValue() == -1 && table.rightValue() == -1) {
        table.addRight(domino);  // Place the first domino on the board
        std::cout << "First domino placed: [" << domino.first << "|" << domino.second << "]" << std::endl;
    }
    else {
        // Check if the domino can be placed at either end
        bool canPlace = false;
        if (domino.first == table.leftValue() || domino.second == table.leftValue()) {
            // Place the domino on the left end
            table.addLeft(domino);
            canPlace = true;
            std::cout << "Domino placed at left: [" << domino.first << "|" << domino.second << "]" << std::endl;
        }
        else if (domino.first == table.rightValue() || domino.second == table.rightValue()) {
            // Place the domino on the right end
            table.addRight(domino);
            canPlace = true;
            std::cout << "Domino placed at right: [" << domino.first << "|" << domino.second << "]" << std::endl;
        }

        if (!canPlace) {
            std::cout << "Cannot place this domino. Drawing a card..." << std::endl;

            // Automatically draw if the chosen domino can't be placed
            if (!remainingDeck.empty()) {
                auto drawnCard = remainingDeck.back();
                remainingDeck.pop_back();
                player.addDomino(drawnCard);
                std::cout << "You drew a domino: [" << drawnCard.first << "|" << drawnCard.second << "]" << std::endl;
            }
            else {
                std::cout << "No more dominoes to draw." << std::endl;
            }
            return;  // End the turn after drawing
        }
    }

    std::cout << (isPlayer1 ? "Player 1's turn over" : "Player 2's turn over") << std::endl;
}

