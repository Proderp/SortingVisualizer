#pragma once
#include "includes.hpp"

class SortEngine {
private:
    std::vector<uin16_t> array;
    
public:
    const std::vector<uint16_t>& getArray() const;
}