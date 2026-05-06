#pragma once
#include "includes.hpp"

class SortEngine {
private:
    std::vector<Element> array;
    uint16_t arraySize{50};
    uint16_t range{100};

    std::random_device rd;
    std::mt19937 twister;
    std::uniform_int_distribution<> distribution;
    
public:
    SortEngine();

    void randomizeArray();
    void randomizeArrayConsecutively();

    const std::vector<Element>& getArray() const;
    const uint16_t getArraySize() const;
};