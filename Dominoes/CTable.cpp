#include "CTable.h"

void CTable::addDomino(const std::pair<int, int>& domino) {
    std::lock_guard<std::mutex> lock(boardMutex);
    board.push_back(domino);
}

void CTable::display() const {
    std::lock_guard<std::mutex> lock(boardMutex);
    std::cout << "Board: ";
    for (const auto& domino : board) {
        std::cout << "[" << domino.first << "|" << domino.second << "] ";
    }
    std::cout << std::endl;
}

int CTable::leftValue() const {
    return board.empty() ? -1 : board.front().first;
}

int CTable::rightValue() const {
    return board.empty() ? -1 : board.back().second;
}
