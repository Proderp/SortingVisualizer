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

    void updateView();
    void updateArrayDimensions(const std::vector<Element>& array);

public:
    UI(sf::RenderWindow& window, const sf::Vector2f& windowSize, const std::vector<Element>& array);    

    void updateUI(const std::vector<Element>& array);

    const ArrayDimensions& getArrayDimensions() const;
};