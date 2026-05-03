#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <random>
#include <numeric>

using Element = uint16_t;
using Index = uint16_t;

constexpr uint16_t DEFAULT_WINDOW_WIDTH{800};
constexpr uint16_t DEFAULT_WINDOW_HEIGHT{600};

constexpr uint16_t ARRAY_SIZE{50};