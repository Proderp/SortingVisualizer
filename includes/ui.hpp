#pragma once
#include "includes.hpp"

struct ArrayDimensions {
    float offsetX;
    float offsetY;

    float barWidth;
    float barHeightUnit;

    float barSpacing;
};

class UI {
private:
    ArrayDimensions arrayDimensions;

    sf::RenderWindow& window;
    sf::View view;

    sf::Vector2f windowSize;

public:
    
    void updateUI(sf::Vector2f newWindowSize);
    void updateView();
    void updateArrayDimensions();

    void setWindowSize(sf::Vector2f newWindowSize);

    const ArrayDimensions& getArrayDimensions() const;
};