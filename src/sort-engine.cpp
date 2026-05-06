#include "sort-engine.hpp"

SortEngine::SortEngine() :
    twister(rd()),
    distribution(1, range)
{
    array.reserve(arraySize);
    randomizeArrayConsecutively();
}

void SortEngine::randomizeArray() {
    array.resize(arraySize);
    for (Index i{0}; i < arraySize; i++) {
        array.at(i) = distribution(twister);
    }
}

void SortEngine::randomizeArrayConsecutively() {
    array.resize(arraySize);
    std::iota(array.begin(), array.end(), 1);
    std::shuffle(array.begin(), array.end(), twister);
}

void SortEngine::bubbleSort() {
    for (Index i{0}; i < array.size(); i++) {
        Index sortedIndex = array.size() - i;
        bool swapMade{false};
        
        for (Index j{0}; j < sortedIndex - 1; j++) {
            if (array.at(j) > array.at(j + 1)) {
                std::swap(array.at(j), array.at(j + 1));
                swapMade = true;
            }
        }

        if (!swapMade) {
            break;
        }
    }
}

const std::vector<Element>& SortEngine::getArray() const {
    return array;
}

const uint16_t SortEngine::getArraySize() const {
    return arraySize;
}