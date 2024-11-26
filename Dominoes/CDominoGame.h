/*
 * File: CDominoGame.h
 * Author: Owen N Chilson
 * Created: 2024-10-26
 *
 * License: MIT
 *
 */

#ifndef CDOMINOGAME_H
#define CDOMINOGAME_H

#include "CDominoes.h"
#include "CTable.h"
#include "CPlayer.h"
#include <thread>
#include <mutex>

class CDominoGame {
private:
    bool gameRunning;
    bool player1Turn;
    CPlayer player1, player2;
    CTable table;
    std::vector<std::pair<int, int>> remainingDeck;
    std::mutex mtx;
    int dominoesPlaced = 0; // Counter for placed dominoes
public:
    CDominoGame();
    void startGame();
    void playerTurn(CPlayer& player, bool isPlayer1);
};

#endif