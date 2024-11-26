#ifndef CRANDOM_H
#define CRANDOM_H

#include <vector>
#include <algorithm>
#include <random>

class CRandom {
public:
    static void shuffle(std::vector<std::pair<int, int>>& dominoes);
};

#endif