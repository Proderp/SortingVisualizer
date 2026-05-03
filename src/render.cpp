#include "render.hpp"

Render::Render(sf::RenderWindow& window, const UI& ui) : 
    window(window),
    ui(ui)
{}

void Render::drawArray(const std::vector<uint16_t>& array) {
    const ArrayDimensions& dimensions = ui.getArrayDimensions();

    for (uint16_t i{0}; i < array.size(); i++) {
        const float xPosition = dimensions.offsetX + (i * dimensions.barWidth) + (i * dimensions.barSpacing);
        rectangle.setPosition({xPosition, dimensions.offsetY});

        const sf::Vector2f barSize = {dimensions.barWidth, dimensions.barHeightUnit * array.at(i)};
        rectangle.setSize(barSize);        

        rectangle.setOrigin({0.f, barSize.y});
        
        window.draw(rectangle);
    }
}
