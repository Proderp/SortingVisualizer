#include "ui.hpp"

UI::UI(sf::RenderWindow& window, const sf::Vector2f& windowSize) :
    window(window),
    windowSize(windowSize)
{
    updateUI();
}

void UI::updateUI() {
    updateView();
}

void UI::updateView() {
    view.setSize(windowSize);
    view.setCenter({windowSize.x / 2.f, windowSize.y / 2.f});

    window.setView(view);
}

void UI::updateArrayDimensions() {

}

const ArrayDimensions& UI::getArrayDimensions() const {
    return arrayDimensions;
}