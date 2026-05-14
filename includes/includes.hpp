#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

using Element = uint32_t;
using Index = uint32_t;

constexpr uint16_t DEFAULT_WINDOW_WIDTH{ 800 };
constexpr uint16_t DEFAULT_WINDOW_HEIGHT{ 600 };

constexpr Index INACTIVE = std::numeric_limits<Index>::max();

constexpr uint16_t MIN_ARRAY_SIZE = 10;
constexpr uint16_t MAX_ARRAY_SIZE = 1'500;

constexpr float MAX_LATENCY = 500.f;

const sf::String stepBackSymbol = L"\u23EE";
const sf::String playSymbol = L"\u25B6";
const sf::String stepForwardSymbol = L"\u23ED";
const sf::String pauseSymbol = L"\u23F8";
const sf::String restartSymbol = L"\u21BB";

const sf::String leftSymbol = L"\u25C0";
const sf::String rightSymbol = L"\u25B6";

const sf::String oOfOne = "O(1)";
const sf::String logN = L"O(log\u2082n)";
const sf::String n = L"O(n)";
const sf::String nLogN = L"O(n log\u2082n)";
const sf::String nSquared = L"O(n\u00B2)";