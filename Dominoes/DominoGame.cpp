#include "DominoGame.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

DominoGame::DominoGame() : currentPlayer(0) {
    initializeDeck();
    dealDominoes();
}

void DominoGame::initializeDeck() {
    for (int i = 0; i <= 6; ++i) {
        for (int j = i; j <= 6; ++j) {
            deck.emplace_back(i, j);
        }
    }
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::time(0)));
}

void DominoGame::dealDominoes() {
    for (int i = 0; i < 7; ++i) {
        players[0].addDomino(deck.back());
        deck.pop_back();
        players[1].addDomino(deck.back());
        deck.pop_back();
    }
}

void DominoGame::displayBoard() const {
    std::cout << "Board: ";
    for (const auto& domino : board) {
        domino.display();
        std::cout << " ";
    }
    std::cout << std::endl;
}

void DominoGame::playTurn() {
    Player& player = players[currentPlayer];
    displayBoard();
    std::cout << "Player " << currentPlayer + 1 << "'s turn. Your hand:" << std::endl;
    player.displayHand();

    int choice;
    std::cout << "Choose a domino to play (1-" << player.hand.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > player.hand.size()) {
        std::cout << "Invalid choice. Turn skipped." << std::endl;
        currentPlayer = 1 - currentPlayer;
        return;
    }

    Domino chosenDomino = player.hand[choice - 1];

    if (board.empty()) {
        board.push_back(chosenDomino);
    }
    else {
        int leftValue = board.front().left;
        int rightValue = board.back().right;

        if (chosenDomino.canConnect(leftValue)) {
            if (chosenDomino.right != leftValue) chosenDomino.flip();
            board.insert(board.begin(), chosenDomino);
        }
        else if (chosenDomino.canConnect(rightValue)) {
            if (chosenDomino.left != rightValue) chosenDomino.flip();
            board.push_back(chosenDomino);
        }
        else {
            std::cout << "This domino can't be played. Turn skipped." << std::endl;
            return;
        }
    }

    player.hand.erase(player.hand.begin() + (choice - 1));

    if (player.hand.empty()) {
        std::cout << "Player " << currentPlayer + 1 << " wins!" << std::endl;
        exit(0);
    }

    currentPlayer = 1 - currentPlayer;
}

void DominoGame::run() {
    while (true) {
        playTurn();
    }
}
