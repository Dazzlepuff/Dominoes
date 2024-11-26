#ifndef CTABLE_H
#define CTABLE_H

#include <vector>
#include <iostream>
#include <mutex>

class CTable {
private:
    std::vector<std::pair<int, int>> board;
    std::mutex boardMutex;

public:
    void addDomino(const std::pair<int, int>& domino);

    void display() ;

    int leftValue() const;

    int rightValue() const;
};

#endif
