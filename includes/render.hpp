#pragma once
#include "includes.hpp"
#include "ui.hpp"

class Render {
private:
    sf::RenderWindow& window;

    const UI& ui;

public:

    Render(sf::RenderWindow& window, const UI& ui);
};