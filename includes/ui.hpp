#pragma once
#include "includes.hpp"

struct ArrayDimensions {
    float offsetX;
    float offsetY;

    float barWidth;
    float barHeightUnit;

    float barSpacing{1.f};
};

struct Button {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::FloatRect bounds;
};

struct ButtonsLayout {
    Button sortButton;
    Button randomizeNormalButton;
    Button randomizeConsecutiveButton;
};

class UI {
private:
    ArrayDimensions arrayDimensions;
    ButtonsLayout randomizeButtonLayout;

    sf::RenderWindow& window;
    sf::View view;

    const sf::Vector2f& windowSize;

    void updateView();
    void updateArrayDimensions(const std::vector<Element>& array);
    void updateRandomizeButtonLayout();

public:
    UI(sf::RenderWindow& window, const sf::Vector2f& windowSize, const std::vector<Element>& array);    

    void updateUI(const std::vector<Element>& array);

    const ArrayDimensions& getArrayDimensions() const;
};