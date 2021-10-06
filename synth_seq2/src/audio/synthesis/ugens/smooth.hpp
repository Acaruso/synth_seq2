#pragma once

#include <vector>

struct Smooth
{
    std::vector<double> history;
    double runningSum{0.0};
    unsigned size{16};
    unsigned writeHead{0};

    Smooth() {
        this->history.reserve(this->size);
        for (size_t i = 0; i < this->size; i++) {
            this->history.push_back(0.0);
        }
    }

    Smooth(unsigned size)
        : size(size)
    {
        this->history.reserve(this->size);
        for (size_t i = 0; i < this->size; i++) {
            this->history.push_back(0.0);
        }
    }

    double get(double in);
};
