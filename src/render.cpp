#include "render.hpp"

Render::Render(sf::RenderWindow& window, const UI& ui) : 
    window(window),
    ui(ui),
    text(font, "")
{
    loadFont();
}

void Render::loadFont() {
    if (!font.openFromFile("../../fonts/Ubuntu-Regular.ttf")) {
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

    text.setCharacterSize(buttonLayout.characterSize);
    text.setFillColor(sf::Color::Black);

    auto drawText = [&](const Button& button) {
        text.setString(button.name);
        setTextOrigin();

        text.setPosition(button.position);
        window.draw(text);
    };
    
    for (const Button* button : buttonLayout.buttons) {
        drawButton(*button);
        drawText(*button);
    }
}

void Render::setTextOrigin() {
	textBounds = text.getLocalBounds();

	text.setOrigin({
		std::round(textBounds.position.x + textBounds.size.x / 2.f),
		std::round(textBounds.position.y + textBounds.size.y / 2.f)
	});
}