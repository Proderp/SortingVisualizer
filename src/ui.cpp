#include "ui.hpp"

UI::UI(sf::RenderWindow& window, const sf::Vector2f& windowSize) :
    window(window),
    windowSize(windowSize)
{
    updateUI();
}

void UI::updateUI() {
    updateView();
    updateArrayDimensions();
}

void UI::updateView() {
    view.setSize(windowSize);
    view.setCenter({windowSize.x / 2.f, windowSize.y / 2.f});

    window.setView(view);
}

void UI::updateArrayDimensions() {
    arrayDimensions.offsetX = windowSize.x * 0.1f;
    arrayDimensions.offsetY = windowSize.y * 0.7f;

    const float allocatedBarArea = windowSize.x - arrayDimensions.offsetX * 2 - arrayDimensions.barSpacing * (ARRAY_SIZE - 1);
    arrayDimensions.barWidth = allocatedBarArea / ARRAY_SIZE;

    const float maxBarHeight = arrayDimensions.offsetY - (windowSize.y * 0.1f);
    arrayDimensions.barHeightUnit = maxBarHeight / 100;
}

const ArrayDimensions& UI::getArrayDimensions() const {
    return arrayDimensions;
}