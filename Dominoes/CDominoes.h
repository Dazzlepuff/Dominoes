/*
 * File: CDominoes.h
 * Author: Owen N Chilson
 * Created: 2024-10-26
 *
 * License: MIT
 *
 */

#ifndef CDOMINOES_H
#define CDOMINOES_H

#include <vector>
#include <utility>

class CDominoes {
public:
    std::vector<std::pair<int, int>> dominoes;

    CDominoes();
    void initialize();
};

#endif
