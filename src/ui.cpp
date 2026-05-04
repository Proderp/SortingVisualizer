#include "ui.hpp"

UI::UI(sf::RenderWindow& window, const sf::Vector2f& windowSize, const std::vector<Element>& array) :
    window(window),
    windowSize(windowSize)
{
    updateUI(array);
}

void UI::updateUI(const std::vector<Element>& array) {
    updateView();
    updateArrayDimensions(array);
    updateButtonLayout();
}

void UI::updateView() {
    view.setSize(windowSize);
    view.setCenter({windowSize.x / 2.f, windowSize.y / 2.f});

    window.setView(view);
}

void UI::updateArrayDimensions(const std::vector<Element>& array) {
    arrayDimensions.offsetX = windowSize.x * 0.1f;
    arrayDimensions.offsetY = windowSize.y * 0.7f;

    const float allocatedBarArea = windowSize.x - arrayDimensions.offsetX * 2 - arrayDimensions.barSpacing * (array.size() - 1);
    arrayDimensions.barWidth = allocatedBarArea / array.size();

    const float maxBarHeight = arrayDimensions.offsetY - (windowSize.y * 0.1f);
    auto maxElement = std::max_element(array.begin(), array.end());
    arrayDimensions.barHeightUnit = maxBarHeight / *maxElement;
}

void UI::updateButtonLayout() {
    const float xSize = (windowSize.y - arrayDimensions.offsetY) / 2.f;
    const sf::Vector2f size = {xSize, xSize / 2.f};
    
    const float yPosition = arrayDimensions.offsetY + xSize;
    
    for (Index i{0}; i < buttonLayout.buttons.size(); i++) {
        Button* button = buttonLayout.buttons.at(i);
        
        button->size = size;

        const float addedSpacing = size.x * (0.5f + i) + margin * i;
        button->position = {arrayDimensions.offsetX + addedSpacing, yPosition};
        
        updateButtonBounds(*button);
    }
}

void UI::updateButtonBounds(Button& button) {
    const sf::Vector2f topLeftCorner = {
        button.position.x - button.size.x / 2.f, 
        button.position.y - button.size.y / 2.f
    };
    
    button.bounds = sf::FloatRect(topLeftCorner, button.size);
}

const ArrayDimensions& UI::getArrayDimensions() const {
    return arrayDimensions;
}

const ButtonLayout& UI::getButtonLayout() const {
    return buttonLayout;
}
