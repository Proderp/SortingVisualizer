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

struct ButtonLayout {
private:
    Button sortButton;
    Button randomizeNormalButton;
    Button randomizeConsecutiveButton;

public:
    std::array<Button*, 3> buttons = {&sortButton, &randomizeNormalButton, &randomizeConsecutiveButton};
};

class UI {
private:
    ArrayDimensions arrayDimensions;
    ButtonLayout buttonLayout;
    
    sf::RenderWindow& window;
    sf::View view;
    
    const sf::Vector2f& windowSize;

    const float margin{15.f};

    void updateView();
    void updateArrayDimensions(const std::vector<Element>& array);
    void updateButtonLayout();
    void updateButtonBounds(Button& button);

public:
    UI(sf::RenderWindow& window, const sf::Vector2f& windowSize, const std::vector<Element>& array);    

    void updateUI(const std::vector<Element>& array);

    const ArrayDimensions& getArrayDimensions() const;

    const ButtonLayout& getButtonLayout() const;
};