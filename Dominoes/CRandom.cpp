/*
 * File: CRandom.cpp
 * Author: Owen N Chilson
 * Created: 2024-10-26
 *
 * License: MIT
 *
 */

#include "CRandom.h"

void CRandom::shuffle(std::vector<std::pair<int, int>>& dominoes) {
    std::shuffle(dominoes.begin(), dominoes.end(), std::default_random_engine(std::random_device{}()));
}