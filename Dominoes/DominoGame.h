#ifndef DOMINOGAME_H
#define DOMINOGAME_H

#include "Domino.h"
#include "Player.h"
#include <vector>

class DominoGame {
private:
    std::vector<Domino> deck;
    std::vector<Domino> board;
    Player players[2];
    int currentPlayer;

    void initializeDeck();

    void dealDominoes();

    void displayBoard() const;

public:
    DominoGame();

    void playTurn();

    void run();
};

#endif
