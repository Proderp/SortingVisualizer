#pragma once
#include "includes.hpp"
#include "ui.hpp"

class Render {
private:
    sf::RenderWindow& window;

    sf::Font firaCodeFont;
    sf::Font segoeFont;

    sf::Text text;
    sf::RectangleShape rectangle;

    sf::Color cold; 
    sf::Color hot;

    const float outlineThickness{-1.f};

    void loadFont();

    void setTextOrigin();

    void drawButton(const Button& button);

public:

    Render(sf::RenderWindow& window, const UI& ui);

    void drawArray(const std::vector<Element>& array, const ArrayDimensions& arrayDimensions, const VisualData& visualData);

    void drawButtonLayout(const ButtonLayout& buttonLayout);

    void drawAnimationSlider(const Slider& animationSlider);
    void drawSliderLayout(const SliderLayout& sliderLayout);

    void drawSortCycler(const SortCycler& sortCycler);
    void drawSortText(const SortCycler& sortCycler);
};