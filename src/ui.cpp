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
    // size = (whatever y is / 3, windowSize.y - offsetY / 3.f)
    // position = (offsetX, offsetY + size.y * 1.5f)
    const float ySize = (windowSize.y - arrayDimensions.offsetY) / 3.f;
    const sf::Vector2f size = {ySize / 3.f, ySize};

    buttonLayout.sortButton.size = size;
    buttonLayout.randomizeNormalButton.size = size;
    buttonLayout.randomizeConsecutiveButton.size = size;

    const float yPosition = arrayDimensions.offsetY + ySize * 1.5f;
    buttonLayout.sortButton.position = {arrayDimensions.offsetX, yPosition};
    buttonLayout.randomizeNormalButton.position = {arrayDimensions.offsetX + size.x * 1.5f, yPosition};
    buttonLayout.randomizeConsecutiveButton.position = {arrayDimensions.offsetX + size.x * 3.f, yPosition};
}

const ArrayDimensions& UI::getArrayDimensions() const {
    return arrayDimensions;
}