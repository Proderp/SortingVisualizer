#include "render.hpp"

Render::Render(sf::RenderWindow& window, const UI& ui) : 
    window(window),
    ui(ui),
    text(font, "")
{}

void Render::loadFont() {
    if (!font.openFromFile("../fonts/Ubuntu-Regular.ttf")) {
        std::cerr << "Error loading font." << std::endl;
    }

    text.setFont(font);
}

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
    
    auto drawButton = [&rect = this->rectangle, &window = this->window](const Button& button) {
        rect.setSize(button.size);
        rect.setPosition(button.position);
        rect.setOrigin(rect.getGeometricCenter());
        
        window.draw(rect);
    };
    
    for (const Button* button : buttonLayout.buttons) {
        drawButton(*button);
    }

    drawButtonText(buttonLayout);
}

void Render::drawButtonText(const ButtonLayout& buttonLayout) {

    auto drawText = [&text = this->text, &window = this->window](const std::string string, const sf::Vector2f position) {
        text.setString(string);
        text.setPosition(position);
        window.draw(text);
    };

    text.setCharacterSize(buttonLayout.characterSize);
    text.setFillColor(sf::Color::Green);

    drawText("Sort", buttonLayout.buttons.at(0)->position);
    drawText("Randomize", buttonLayout.buttons.at(1)->position);
    drawText("Consecutive", buttonLayout.buttons.at(2)->position);
}