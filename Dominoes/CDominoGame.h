// CDominoGame.h
#ifndef CDOMINOGAME_H
#define CDOMINOGAME_H

#include "CDominoes.h"
#include "CTable.h"
#include "CPlayer.h"
#include <thread>
#include <mutex>

class CDominoGame {
public:
    CDominoGame();
    void startGame();
    void playerTurn(CPlayer& player, bool isPlayer1);
    bool gameRunning;
    bool player1Turn; // Flag to control whose turn it is

private:
    CTable table;
    CPlayer player1, player2;
    std::mutex mtx;  // To ensure only one player can play at a time
};

#endif
