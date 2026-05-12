#include "render.hpp"

Render::Render(sf::RenderWindow& window, const UI& ui) : 
    window(window),
    text(font, ""),
    cold(24, 90, 157),
    hot(191, 0, 255)
{
    loadFont();
}

void Render::loadFont() {
    if (!font.openFromFile("../../fonts/Ubuntu-Regular.ttf")) {
        std::cerr << "Error loading font." << std::endl;
    }

    text.setFont(font);
}

void Render::drawArray(const std::vector<Element>& array, const ArrayDimensions& arrayDimensions, const VisualData& visualData) {
    for (Index i{0}; i < array.size(); i++) {
        const float normalizedValue = static_cast<float>(array.at(i)) / array.size();

        const uint8_t r = cold.r + normalizedValue * (hot.r - cold.r);
        const uint8_t g = cold.g + normalizedValue * (hot.g - cold.g);
        const uint8_t b = cold.b + normalizedValue * (hot.b - cold.b);

        rectangle.setFillColor(sf::Color(r, g, b));

        const float xPosition = arrayDimensions.offsetX + (i * arrayDimensions.barWidth) + (i * arrayDimensions.barSpacing);
        rectangle.setPosition({xPosition, arrayDimensions.offsetY});

        const sf::Vector2f barSize = {arrayDimensions.barWidth, arrayDimensions.barHeightUnit * array.at(i)};
        rectangle.setSize(barSize);        

        rectangle.setOrigin({0.f, barSize.y});
        
        // rectangle.setFillColor(sf::Color::White);
        
        // // for swaps and comaprisons
        // if (visualData.activeOne != INACTIVE and visualData.activeTwo != INACTIVE) {
        //     if (visualData.activeOne == i or visualData.activeTwo == i) {
        //         rectangle.setFillColor(sf::Color::Red);
        //     }
        // }

        // if (visualData.sortedElements.size() == array.size() and visualData.sortedElements.at(i)) {
        //     rectangle.setFillColor(sf::Color::Green);
        // }

        // if (visualData.isOverwrite and i == visualData.activeOne) {
        //     rectangle.setFillColor(sf::Color::Yellow);
        // } 

        // if (visualData.pivot != INACTIVE and i == visualData.pivot) {
        //     rectangle.setFillColor(sf::Color(255, 165, 0));
        // }

        window.draw(rectangle);
    }
}

void Render::drawButton(const Button& button) {
    rectangle.setSize(button.size);
    rectangle.setPosition(button.position);
    rectangle.setOrigin(rectangle.getGeometricCenter());
    
    window.draw(rectangle);
}

void Render::drawButtonLayout(const ButtonLayout& buttonLayout) {   
       
    rectangle.setFillColor(sf::Color::White);

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
    // draw the rectangle up to the point where the thumb is
    rectangle.setFillColor(sf::Color(255, 50, 50));
    const float startOfTrack = animationSlider.position.x;
    
    const float thumbXPosition = animationSlider.thumb.position.x;
    const float upToThumbWitdh = thumbXPosition - startOfTrack + animationSlider.thumb.size.x / 2.f;
    
    rectangle.setPosition(animationSlider.position);
    rectangle.setSize({upToThumbWitdh, animationSlider.size.y});
    rectangle.setOrigin({0, animationSlider.size.y / 2.f});
    
    window.draw(rectangle);
    
    const float endOfTrack = startOfTrack + animationSlider.size.x;
    const float thumbToEndWidth = endOfTrack - upToThumbWitdh;
    rectangle.setFillColor(sf::Color(100, 100, 100));
    rectangle.setPosition({upToThumbWitdh, animationSlider.position.y});
    rectangle.setSize({thumbToEndWidth, animationSlider.size.y});
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
        drawButton(slider->thumb);
    }
}

void Render::setTextOrigin() {
	const sf::FloatRect bounds = text.getLocalBounds();

	text.setOrigin({
		std::round(bounds.position.x + bounds.size.x / 2.f),
		std::round(bounds.position.y + bounds.size.y / 2.f)
	});
}