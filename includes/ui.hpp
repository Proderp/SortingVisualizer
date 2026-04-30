#pragma once
#include "includes.hpp"

struct ArrayDimensions {
    float offsetX;
    float offsetY;

    float barWidth;
    float barHeightUnit;

    float barSpacing{1.f};
};

class UI {
private:
    ArrayDimensions arrayDimensions;

    sf::RenderWindow& window;
    sf::View view;

    const sf::Vector2f& windowSize;

public:
    UI(sf::RenderWindow& window, const sf::Vector2f& windowSize);    

    void updateUI();
    void updateView();
    void updateArrayDimensions();

    const ArrayDimensions& getArrayDimensions() const;
};