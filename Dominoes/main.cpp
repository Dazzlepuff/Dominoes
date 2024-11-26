#include "CDominoes.h"
#include "CTable.h"
#include "CPlayer.h"
#include <thread>
#include <iostream>

void playerTurn(CPlayer& player, CTable& table) {
    while (true) {
        std::cout << "Player's turn:" << std::endl;
        player.displayHand();
        table.display();

        int choice;
        std::cout << "Select domino to play (1-" << player.hand.size() << "): ";
        std::cin >> choice;

        if (choice < 1 || choice > player.hand.size()) {
            std::cout << "Invalid choice. Try again." << std::endl;
            continue;
        }

        auto domino = player.playDomino(choice - 1);
        table.addDomino(domino);
        break;
    }
}

int main() {
    CDominoes deck;
    CTable table;
    CPlayer player1, player2;

    for (int i = 0; i < 7; ++i) {
        player1.addDomino(deck.dominoes.back());
        deck.dominoes.pop_back();
        player2.addDomino(deck.dominoes.back());
        deck.dominoes.pop_back();
    }

    std::thread p1(playerTurn, std::ref(player1), std::ref(table));
    std::thread p2(playerTurn, std::ref(player2), std::ref(table));

    p1.join();
    p2.join();

    return 0;
}
