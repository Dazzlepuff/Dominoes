/*
 * File: CPlayer.h
 * Author: Owen N Chilson
 * Created: 2024-10-26
 *
 * License: MIT
 *
 */

#ifndef CPLAYER_H
#define CPLAYER_H

#include <vector>
#include <iostream>
#include <mutex>

class CPlayer {
public:
    std::vector<std::pair<int, int>> hand;
    std::mutex handMutex;

    void addDomino(const std::pair<int, int>& domino);

    void displayHand();

    std::pair<int, int> playDomino(int index);
};

#endif
