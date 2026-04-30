#include "sort-engine.hpp"

SortEngine::SortEngine() :
    twister(rd()),
    distribution(1, 100)
{}

const std::vector<uint16_t>& SortEngine::getArray() const {
    return array;
}