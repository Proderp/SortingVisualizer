#include "ui.hpp"

UI::UI(sf::RenderWindow& window, const sf::Vector2f windowSize) :
    window(window),
    windowSize(windowSize)
{

}

void UI::updateUI(sf::Vector2f newWindowSize) {
    setWindowSize(newWindowSize);
    updateView();
}

void UI::updateView() {
    view.setSize(windowSize);
    view.setCenter({windowSize.x / 2.f, windowSize.y / 2.f});

    window.setView(view);
}

void UI::updateArrayDimensions() {

}

void UI::setWindowSize(sf::Vector2f newWindowSize) {
    windowSize = newWindowSize;
}

const ArrayDimensions& UI::getArrayDimensions() const {
    return arrayDimensions;
}