#include "ui.hpp"

void UI::updateUI(sf::Vector2f newWindowSize) {
    setWindowSize(newWindowSize);
}

void UI::updateView() {

}

void UI::updateArrayDimensions() {

}

void UI::setWindowSize(sf::Vector2f newWindowSize) {
    windowSize = newWindowSize;
}

const ArrayDimensions& UI::getArrayDimensions() const {
    return arrayDimensions;
}