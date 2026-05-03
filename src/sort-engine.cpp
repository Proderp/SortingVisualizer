#include "sort-engine.hpp"

SortEngine::SortEngine() :
    twister(rd()),
    distribution(1, RANGE)
{
    for (uint16_t i{0}; i < ARRAY_SIZE; i++) {
        array.push_back(distribution(twister));
    }
}

const std::vector<uint16_t>& SortEngine::getArray() const {
    return array;
}