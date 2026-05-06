#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include <string>
#include <map>

using Element = uint16_t;
using Index = uint16_t;

constexpr uint16_t DEFAULT_WINDOW_WIDTH{ 800 };
constexpr uint16_t DEFAULT_WINDOW_HEIGHT{ 600 };

enum class ButtonType { Sort, Randomize, Consecutive, None };