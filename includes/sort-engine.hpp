#pragma once
#include "includes.hpp"

class SortEngine {
private:
    std::vector<uint16_t> array;

public:
    const std::vector<uint16_t>& getArray() const;
};