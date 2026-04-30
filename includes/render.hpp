#pragma once
#include "includes.hpp"
#include "ui.hpp"

class Render {
public:
    sf::RenderWindow& window;

    Render(sf::RenderWindow& window);
};