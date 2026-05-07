#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include <string>

using Element = uint16_t;
using Index = uint16_t;

constexpr uint16_t DEFAULT_WINDOW_WIDTH{ 800 };
constexpr uint16_t DEFAULT_WINDOW_HEIGHT{ 600 };

constexpr Index INACTIVE = std::numeric_limits<Index>::max();

struct VisualState {
    Index activeOne{INACTIVE};
    Index activeTwo{INACTIVE};
    Index currentPivot{INACTIVE};
    std::vector<bool> isSorted; 
};