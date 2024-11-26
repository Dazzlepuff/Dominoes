/*
 * File: CDominoGame.cpp
 * Author: Owen N Chilson
 * Created: 2024-10-26
 *
 * License: MIT
 *
 */

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
    }
    else {
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
            dominoesPlaced++; // Increment placed domino counter
        }
        else {
            // Check if the domino can be placed at either end
            bool canPlace = false;
            if (domino.first == table.leftValue() || domino.second == table.leftValue()) {
                table.addLeft(domino);
                canPlace = true;
                std::cout << "Domino placed at left: [" << domino.first << "|" << domino.second << "]" << std::endl;
                dominoesPlaced++; // Increment placed domino counter
            }
            else if (domino.first == table.rightValue() || domino.second == table.rightValue()) {
                table.addRight(domino);
                canPlace = true;
                std::cout << "Domino placed at right: [" << domino.first << "|" << domino.second << "]" << std::endl;
                dominoesPlaced++; // Increment placed domino counter
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
            }
        }
    }

    // Check if the player has no dominoes left
    if (player.hand.empty()) {
        std::cout << (isPlayer1 ? "Player 1 wins!" : "Player 2 wins!") << std::endl;

        // Display summary information
        std::cout << "Game Over Summary:" << std::endl;
        std::cout << "Player 1 dominoes left: " << player1.hand.size() << std::endl;
        std::cout << "Player 2 dominoes left: " << player2.hand.size() << std::endl;
        std::cout << "Dominoes remaining in stack: " << remainingDeck.size() << std::endl;
        std::cout << "Total dominoes placed on the table: " << dominoesPlaced << std::endl;

        // Visual display of remaining dominoes
        std::cout << "Player 1's remaining dominoes: ";
        player1.displayHand();
        std::cout << "Player 2's remaining dominoes: ";
        player2.displayHand();

        std::cout << "Remaining dominoes in stack: ";
        for (const auto& domino : remainingDeck) {
            std::cout << "[" << domino.first << "|" << domino.second << "] ";
        }
        std::cout << std::endl;

        std::cout << "Dominoes placed on the table: ";
        table.display();

        gameRunning = false;
        return;
    }

    std::cout << (isPlayer1 ? "Player 1's turn over" : "Player 2's turn over") << std::endl;
}