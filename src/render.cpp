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

void Render::drawArray(const std::vector<Element>& array, const VisualData& visualData) {
    const ArrayDimensions& dimensions = ui.getArrayDimensions();

    for (Index i{0}; i < array.size(); i++) {
        const float xPosition = dimensions.offsetX + (i * dimensions.barWidth) + (i * dimensions.barSpacing);
        rectangle.setPosition({xPosition, dimensions.offsetY});

        const sf::Vector2f barSize = {dimensions.barWidth, dimensions.barHeightUnit * array.at(i)};
        rectangle.setSize(barSize);        

        rectangle.setOrigin({0.f, barSize.y});
        
        rectangle.setFillColor(sf::Color::White);
        
        // for swaps and comaprisons
        if (visualData.activeOne != INACTIVE and visualData.activeTwo != INACTIVE) {
            if (visualData.activeOne == i or visualData.activeTwo == i) {
                rectangle.setFillColor(sf::Color::Red);
            }
        }

        // for marking sorted and overwrites
        if (visualData.activeOne != INACTIVE or visualData.isSorted) {
            if (visualData.sortedElements.at(i) and !visualData.sortedElements.empty()) {
                rectangle.setFillColor(sf::Color::Green);
            }
        }

        if (visualData.isOverwrite and i == visualData.activeOne) {
            rectangle.setFillColor(sf::Color::Yellow);
        } 

        window.draw(rectangle);
    }
}

void Render::drawButtons(const ButtonLayout& buttonLayout) {   
       
    rectangle.setFillColor(sf::Color::White);

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
	const sf::FloatRect bounds = text.getLocalBounds();

	text.setOrigin({
		std::round(bounds.position.x + bounds.size.x / 2.f),
		std::round(bounds.position.y + bounds.size.y / 2.f)
	});
}