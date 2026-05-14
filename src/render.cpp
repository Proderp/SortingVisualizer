#include "render.hpp"

Render::Render(sf::RenderWindow& window, const UI& ui) : 
    window(window),
    text(firaCodeFont, ""),
    cold(24, 90, 157),
    hot(191, 0, 255)
{
    loadFont();
}

void Render::loadFont() {
    if (!firaCodeFont.openFromFile("../../fonts/FiraCode-Regular.ttf")) {
        std::cerr << "Error loading Fira Code." << std::endl;
    }

    if (!segoeFont.openFromFile("../../fonts/seguisym.ttf")) {
        std::cerr << "Error loading Segoe." << std::endl;
    }

    text.setFont(firaCodeFont);
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
       
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(outlineThickness);
    rectangle.setOutlineColor(sf::Color::White);

    text.setFillColor(sf::Color::White);
    
    auto drawText = [&](const Button& button) {
        text.setString(button.name);
        
        bool isControlButton = button.id == ButtonType::StepBack or button.id == ButtonType::Play or button.id == ButtonType::StepForward;
        if (isControlButton) {
            text.setFont(segoeFont);
        } else {
            text.setFont(firaCodeFont);
        }

        text.setCharacterSize(button.charSize);
        text.setLetterSpacing(3.f);
        setTextOrigin();

        text.setPosition(button.position);
        window.draw(text);
    };
    
    for (const Button* button : buttonLayout.buttons) {
        drawButton(*button);
        drawText(*button);
    }

    rectangle.setOutlineThickness(0);
    rectangle.setOutlineColor(sf::Color::Transparent);
}

void Render::drawAnimationSlider(const Slider& animationSlider) {
    // draw the rectangle up to the point where the thumb is
    rectangle.setFillColor(cold);

    const float thumbRadius = animationSlider.thumb.size.x / 2.f;
    const float startOfTrack = animationSlider.position.x + thumbRadius;
    
    const float thumbXPosition = animationSlider.thumb.position.x;
    const float upToThumbWitdh = thumbXPosition - startOfTrack;
    
    rectangle.setPosition(animationSlider.position);
    rectangle.setSize({upToThumbWitdh, animationSlider.size.y});
    rectangle.setOrigin({0, animationSlider.size.y / 2.f});
    
    window.draw(rectangle);
    
    const float endOfTrack = startOfTrack + animationSlider.size.x - thumbRadius;
    const float thumbToEndWidth = endOfTrack - thumbXPosition;

    rectangle.setFillColor(hot);
    rectangle.setPosition({thumbXPosition, animationSlider.position.y});
    rectangle.setSize({thumbToEndWidth, animationSlider.size.y});
    rectangle.setOrigin({0, animationSlider.size.y / 2.f});

    window.draw(rectangle);

    rectangle.setFillColor(sf::Color::White);
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

void Render::drawSortCycler(const SortCycler& sortCycler) {
    drawSortText(sortCycler);
    
    rectangle.setPosition(sortCycler.leftArrow.position);
    rectangle.setSize(sortCycler.leftArrow.size);
    rectangle.setOutlineThickness(outlineThickness);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOrigin(rectangle.getGeometricCenter());
    window.draw(rectangle);

    text.setString(sortCycler.leftArrow.name);
    setTextOrigin();
    text.setPosition(sortCycler.leftArrow.position);
    window.draw(text);

    rectangle.setPosition(sortCycler.rightArrow.position);
    window.draw(rectangle);

    text.setString(sortCycler.rightArrow.name);
    setTextOrigin();
    text.setPosition(sortCycler.rightArrow.position);
    window.draw(text);

    text.setScale({1.f, 1.f});
    rectangle.setOutlineThickness(0);
    rectangle.setOutlineColor(sf::Color::Transparent);
    rectangle.setFillColor(sf::Color::White);
}

void Render::drawSortText(const SortCycler& sortCycler) {
    switch (sortCycler.algorithm) {
        using enum Algorithm;
        case Bubble:
            text.setString("BUBBLE");
            break;
        case Insertion:
            text.setString("INSERTION");
            break;
        case Merge:
            text.setString("MERGE");
            break;
        case Quick:
            text.setString("QUICK");
            break;
    }

    text.setCharacterSize(sortCycler.charSize);
    setTextOrigin();
    
    text.setPosition(sortCycler.position);
    window.draw(text);
}

void Render::drawHUD(const HUD& hud) {
    
}

void Render::setTextOrigin() {
	const sf::FloatRect bounds = text.getLocalBounds();

	text.setOrigin({
		std::round(bounds.position.x + bounds.size.x / 2.f),
		std::round(bounds.position.y + bounds.size.y / 2.f)
	});
}