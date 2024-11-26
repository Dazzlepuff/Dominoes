#include "CPlayer.h"

void CPlayer::addDomino(const std::pair<int, int>& domino) {
    std::lock_guard<std::mutex> lock(handMutex);
    hand.push_back(domino);
}

void CPlayer::displayHand() {
    std::lock_guard<std::mutex> lock(handMutex);
    for (size_t i = 0; i < hand.size(); ++i) {
        std::cout << i + 1 << ": [" << hand[i].first << "|" << hand[i].second << "] ";
    }
    std::cout << std::endl;
}

std::pair<int, int> CPlayer::playDomino(int index) {
    std::lock_guard<std::mutex> lock(handMutex);

    // Check if the index is within bounds
    if (index < 0 || index >= hand.size()) {
        std::cerr << "Error: Index out of range.\n";
        return std::pair<int, int>{-1, -1};  // Return a default value indicating an error
    }

    // Get the domino to be played
    auto domino = hand[index];

    // Erase the selected domino
    hand.erase(hand.begin() + index);

    // Return the selected domino
    return domino;
}

