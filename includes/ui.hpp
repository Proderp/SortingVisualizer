#pragma once
#include "includes.hpp"
#include "ui-elements.hpp"

class UI {
private:
    ArrayDimensions arrayDimensions;
    ButtonLayout buttonLayout;

    Slider animationSlider;

    sf::RenderWindow& window;
    sf::View view;
    
    const sf::Vector2f& windowSize;

    const float margin{15.f};

    void updateView();
    
    void updateArrayDimensions(const std::vector<Element>& array);
    
    void updateButtonLayout();
    void updateButtonBounds(Button& button);
    void updateCharacterSize();

    void updateAnimationSlider();
public:
    UI(sf::RenderWindow& window, const sf::Vector2f& windowSize, const std::vector<Element>& array);    

    void updateUI(const std::vector<Element>& array);

    const ButtonType findClickedButton(const sf::Vector2f mousePosition);

    const ArrayDimensions& getArrayDimensions() const;

    const ButtonLayout& getButtonLayout() const;

    const Slider& getAnimationSlider() const;
};