#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include <string>

using Element = uint32_t;
using Index = uint32_t;

constexpr uint16_t DEFAULT_WINDOW_WIDTH{ 800 };
constexpr uint16_t DEFAULT_WINDOW_HEIGHT{ 600 };

constexpr Index INACTIVE = std::numeric_limits<Index>::max();

constexpr uint16_t MIN_ARRAY_SIZE = 10;
constexpr uint16_t MAX_ARRAY_SIZE = 500;

constexpr float MAX_LATENCY = 500.f;

struct VisualData {
    Index activeOne{INACTIVE}, activeTwo{INACTIVE};
    bool isOverwrite{false};

    bool isSorted{false};
    std::vector<bool> sortedElements; 
};