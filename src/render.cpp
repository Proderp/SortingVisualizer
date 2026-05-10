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

        if (!visualData.sortedElements.empty() and visualData.sortedElements.at(i)) {
            rectangle.setFillColor(sf::Color::Green);
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

void Render::drawAnimationSlider(const Slider& animationSlider) {
    rectangle.setFillColor(sf::Color(100, 100, 100));
    rectangle.setPosition(animationSlider.position);
    rectangle.setSize(animationSlider.size);
    rectangle.setOrigin({0, animationSlider.size.y / 2.f});

    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(animationSlider.thumb.position);
    rectangle.setSize(animationSlider.thumb.size);
    rectangle.setOrigin(rectangle.getGeometricCenter());

    window.draw(rectangle);
}

void Render::drawSliderLayout(const SliderLayout& sliderLayout) {
    for (const Slider* slider : sliderLayout.sliders) {
        rectangle.setFillColor(sf::Color(100, 100, 100));
        rectangle.setPosition(slider->position);
        rectangle.setSize(slider->size);

        const sf::Vector2f middleLeft = {0, slider->size.y / 2.f}; 
        rectangle.setOrigin(middleLeft);

        window.draw(rectangle);

        rectangle.setFillColor(sf::Color::Green);
        rectangle.setPosition(slider->thumb.position);
        rectangle.setSize(slider->thumb.size);
        rectangle.setOrigin(rectangle.getGeometricCenter());

        window.draw(rectangle);
    }
}

void Render::highlightRect(sf::FloatRect floatRect) {
    sf::RectangleShape visualRect;
    sf::CircleShape dot(2);
    dot.setFillColor(sf::Color::Transparent);
    dot.setOrigin(dot.getGeometricCenter());
    dot.setOutlineThickness(-1.f);
    dot.setOutlineColor(sf::Color::Blue);

    visualRect.setSize(floatRect.size);
    visualRect.setPosition(floatRect.position);
    dot.setPosition(floatRect.position);
    window.draw(dot);

    visualRect.setFillColor(sf::Color::Transparent);
    visualRect.setOutlineColor(sf::Color::Red);
    visualRect.setOutlineThickness(1.0f);
    dot.setPosition(floatRect.position);
    window.draw(dot);

    window.draw(visualRect);
}

void Render::setTextOrigin() {
	const sf::FloatRect bounds = text.getLocalBounds();

	text.setOrigin({
		std::round(bounds.position.x + bounds.size.x / 2.f),
		std::round(bounds.position.y + bounds.size.y / 2.f)
	});
}