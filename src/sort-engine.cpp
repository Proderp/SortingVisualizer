#include "sort-engine.hpp"

SortEngine::SortEngine() :
    twister(rd()),
    distribution(1, ARRAY_SIZE)
{
    array.reserve(ARRAY_SIZE);
    randomizeArray();
    //randomizeArrayConsecutively();
}

void SortEngine::randomizeArray() {
    array.resize(ARRAY_SIZE);
    for (Index i{0}; i < ARRAY_SIZE; i++) {
        array.at(i) = distribution(twister);
    }
}

void SortEngine::randomizeArrayConsecutively() {
    array.resize(ARRAY_SIZE);
    std::iota(array.begin(), array.end(), 1);
    std::shuffle(array.begin(), array.end(), twister);
}

const std::vector<Element>& SortEngine::getArray() const {
    return array;
}