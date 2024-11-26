#include "CDominoes.h"
#include "CRandom.h"

CDominoes::CDominoes() {
    initialize();
}

void CDominoes::initialize() {
    dominoes.clear();
    for (int i = 0; i <= 6; ++i) {
        for (int j = i; j <= 6; ++j) {
            dominoes.emplace_back(i, j);
        }
    }
    CRandom::shuffle(dominoes);
}
