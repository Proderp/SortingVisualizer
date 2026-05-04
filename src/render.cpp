#include "render.hpp"

Render::Render(sf::RenderWindow& window, const UI& ui) : 
    window(window),
    ui(ui),
    text(font, "")
{}

void Render::drawArray(const std::vector<Element>& array) {
    const ArrayDimensions& dimensions = ui.getArrayDimensions();

    for (Index i{0}; i < array.size(); i++) {
        const float xPosition = dimensions.offsetX + (i * dimensions.barWidth) + (i * dimensions.barSpacing);
        rectangle.setPosition({xPosition, dimensions.offsetY});

        const sf::Vector2f barSize = {dimensions.barWidth, dimensions.barHeightUnit * array.at(i)};
        rectangle.setSize(barSize);        

        rectangle.setOrigin({0.f, barSize.y});
        
        window.draw(rectangle);
    }
}

void Render::drawButtons(const ButtonLayout& buttonLayout) {

    auto drawButton = [&](const Button& button) {
        rectangle.setSize(button.size);
        rectangle.setPosition(button.position);
        rectangle.setOrigin(rectangle.getGeometricCenter());
        
        window.draw(rectangle);
    };

    for (const Button* button : buttonLayout.buttons) {
        drawButton(*button);
    }
}