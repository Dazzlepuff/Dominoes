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
    auto domino = hand[index];  // Copy the domino instead of returning a reference
    hand.erase(hand.begin() + index);
    return domino;  // Return the copied domino
}
