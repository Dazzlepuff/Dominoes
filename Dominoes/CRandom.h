/*
 * File: CRandom.h
 * Author: Owen N Chilson
 * Created: 2024-10-26
 *
 * License: MIT
 *
 */

#ifndef CRANDOM_H
#define CRANDOM_H

#include <vector>
#include <algorithm>
#include <random>

class CRandom {
public:
    static void shuffle(std::vector<std::pair<int, int>>& dominoes);

    bool randomBool() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 1);
        return dis(gen);
    }
};

#endif