#pragma once
#include "includes.hpp"

class SortEngine {
private:
    std::vector<uint16_t> array;

    std::random_device rd;
    std::mt19937 twister;
    std::uniform_int_distribution<> distribution;

public:
    SortEngine();

    const std::vector<uint16_t>& getArray() const;
};