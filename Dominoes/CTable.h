#ifndef CTABLE_H
#define CTABLE_H

#include <deque>  // Use deque for efficient insertion at both ends
#include <iostream>
#include <mutex>

class CTable {
private:
    std::deque<std::pair<int, int>> board;  // Use deque for left/right operations
    mutable std::mutex boardMutex;          // Mutex for thread safety

    // Helper function to flip a domino
    std::pair<int, int> flipDomino(const std::pair<int, int>& domino) const;

public:
    // Add domino to the left
    void addLeft(const std::pair<int, int>& domino);

    // Add domino to the right
    void addRight(const std::pair<int, int>& domino);

    // Display the board
    void display() const;

    // Get the value at the left end of the board
    int leftValue() const;

    // Get the value at the right end of the board
    int rightValue() const;
};

#endif // CTABLE_H
