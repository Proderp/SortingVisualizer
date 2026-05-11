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

    sf::Color cold; 
    sf::Color hot;

    void loadFont();

    void setTextOrigin();

    void drawButton(const Button& button);

public:

    Render(sf::RenderWindow& window, const UI& ui);

    void drawArray(const std::vector<Element>& array, const VisualData& visualData);

    void drawButtonLayout(const ButtonLayout& buttonLayout);

    void drawAnimationSlider(const Slider& animationSlider);
    void drawSliderLayout(const SliderLayout& sliderLayout);
};