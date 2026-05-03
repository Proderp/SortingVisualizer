#pragma once
#include "includes.hpp"

class SortEngine {
private:
    std::vector<Element> array;

    std::random_device rd;
    std::mt19937 twister;
    std::uniform_int_distribution<> distribution;

    void randomizeArray();
    void randomizeArrayConsecutively();

public:
    SortEngine();

    const std::vector<Element>& getArray() const;
};