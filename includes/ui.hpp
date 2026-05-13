#pragma once
#include "includes.hpp"
#include "ui-elements.hpp"

class UI {
private:
    ArrayDimensions arrayDimensions;
    ButtonLayout buttonLayout;
    SliderLayout sliderLayout;
    Slider animationSlider;
    SortCycler sortCycler;

    sf::RenderWindow& window;
    sf::View view;
    
    const sf::Vector2f& windowSize;

    const float margin{20.f};

    void updateView();
    
    void updateButtonLayout();
    void updateRandomizeButtons();
    void updateControlButtons();
    void updateButtonBounds(Button& button);
    void updateCharacterSize();

    void updateArrayDimensions(const std::vector<Element>& array);

    SliderEvent updateSliderPercentage(Slider& slider, const float mouseX);

    void updateSortCycler();
public:
    UI(sf::RenderWindow& window, const sf::Vector2f& windowSize, const std::vector<Element>& array);    
    
    void updateUI(const std::vector<Element>& array);
    void updateAnimationSlider();
    void updateSliderLayout();

    const ButtonType findClickedButton(const sf::Vector2f mousePosition);
    std::optional<SliderEvent> checkSliderClick(const sf::Vector2f mousePosition, const ButtonType activeDragSlider, const uint16_t actionSize);

    const ArrayDimensions& getArrayDimensions() const;
    const ButtonLayout& getButtonLayout() const;
    const Slider& getAnimationSlider() const;
    const SliderLayout& getSliderLayout() const;
    const SortCycler& getSortCycler() const;

    void setAnimationPercentage(const float percentage);
    void resetAnimationSlider();

    void setArraySizePercentage(const float percentage);

    void setLatencyPercentage(const float percentage);

    void setPlayButtonSymbol(const sf::String newSymbol);

    void setSortCycleAlgorithm(const Index index);
};