/*
 * File: CTable.cpp
 * Author: Owen N Chilson
 * Created: 2024-10-26
 *
 * License: MIT
 *
 */

#include "CTable.h"

// Flips a domino by swapping its values
std::pair<int, int> CTable::flipDomino(const std::pair<int, int>& domino) const {
    return { domino.second, domino.first };  // Swap the values
}

// Adds a domino to the left end of the board
void CTable::addLeft(const std::pair<int, int>& domino) {
    std::lock_guard<std::mutex> lock(boardMutex);

    if (board.empty() || domino.second == board.front().first) {
        board.push_front(domino);  // Add domino as is
    }
    else if (domino.first == board.front().first) {
        board.push_front(flipDomino(domino));  // Flip domino before adding
    }
    else {
        std::cerr << "Error: Cannot add domino to the left. No match.\n";
    }
}

// Adds a domino to the right end of the board
void CTable::addRight(const std::pair<int, int>& domino) {
    std::lock_guard<std::mutex> lock(boardMutex);

    if (board.empty() || domino.first == board.back().second) {
        board.push_back(domino);  // Add domino as is
    }
    else if (domino.second == board.back().second) {
        board.push_back(flipDomino(domino));  // Flip domino before adding
    }
    else {
        std::cerr << "Error: Cannot add domino to the right. No match.\n";
    }
}

// Displays the current state of the board
void CTable::display() const {
    std::lock_guard<std::mutex> lock(boardMutex);
    std::cout << "Board: ";
    for (const auto& domino : board) {
        std::cout << "[" << domino.first << "|" << domino.second << "] ";
    }
    std::cout << std::endl;
}

// Returns the left value of the board
int CTable::leftValue() const {
    std::lock_guard<std::mutex> lock(boardMutex);
    return board.empty() ? -1 : board.front().first;  // Return -1 if board is empty
}

// Returns the right value of the board
int CTable::rightValue() const {
    std::lock_guard<std::mutex> lock(boardMutex);
    return board.empty() ? -1 : board.back().second;  // Return -1 if board is empty
}
