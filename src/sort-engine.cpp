#include "sort-engine.hpp"

SortEngine::SortEngine() :
    twister(rd()),
    distribution(1, RANGE)
{
    for (Index i{0}; i < ARRAY_SIZE; i++) {
        array.push_back(distribution(twister));
    }
}

const std::vector<Element>& SortEngine::getArray() const {
    return array;
}