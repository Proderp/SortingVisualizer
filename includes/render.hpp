#pragma once
#include "includes.hpp"
#include "ui.hpp"

class Render {
private:
    sf::RenderWindow& window;

    const UI& ui;

    sf::Font font;
    sf::Text text;
    sf::RectangleShape rectangle;

    void loadFont();

public:

    Render(sf::RenderWindow& window, const UI& ui);

    void drawArray(const std::vector<Element>& array);

    void drawButtons(const ButtonLayout& buttonLayout);
};