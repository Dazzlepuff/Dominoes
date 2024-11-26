#include "CRandom.h"

void CRandom::shuffle(std::vector<std::pair<int, int>>& dominoes) {
    std::shuffle(dominoes.begin(), dominoes.end(), std::default_random_engine(std::random_device{}()));
}