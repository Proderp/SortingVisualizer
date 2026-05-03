#include "sort-engine.hpp"

SortEngine::SortEngine() :
    twister(rd()),
    distribution(1, RANGE)
{
    array.reserve(ARRAY_SIZE);
}

void SortEngine::randomizeArray() {
    for (Index i{0}; i < ARRAY_SIZE; i++) {
        array.push_back(distribution(twister));
    }
}

void SortEngine::randomizeArrayConsecutively() {

}

const std::vector<Element>& SortEngine::getArray() const {
    return array;
}