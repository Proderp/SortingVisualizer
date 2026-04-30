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
    
    void updateUI();
    void updateView();
    void updateArrayDimensions();

    const ArrayDimensions& getArrayDimensions() const;
};