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

        if (button.name == playSymbol and button.id == ButtonType::Play) {
            sf::Vector2f newPosition = button.position + sf::Vector2f(button.size.x * 0.05f, 0.f);
            text.setPosition(newPosition);
        } else {
            text.setPosition(button.position);
        }
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

    drawTrack(animationSlider);
    rectangle.setFillColor(sf::Color::White);
    drawButton(animationSlider.thumb);
}

void Render::drawSliderLayout(const SliderLayout& sliderLayout) {
    text.setCharacterSize(sliderLayout.characterSize);
    text.setFont(firaCodeFont);
    text.setFillColor(sf::Color::White);
    text.setLetterSpacing(1.f);

    for (const Slider* slider : sliderLayout.sliders) {
        drawTrack(*slider);
        rectangle.setFillColor(sf::Color::White);
        drawButton(slider->thumb);
        
        text.setString(slider->thumb.name);
        
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({0.f, std::round(bounds.position.y + bounds.size.y)});
        
        const float distanceAboveSlider = slider->thumb.size.y;
        text.setPosition(slider->position - sf::Vector2f(0.f, distanceAboveSlider));
        window.draw(text);

        sf::String value;
        if (slider->thumb.id == ButtonType::ArraySizeSlider) {
            value = std::to_string(static_cast<size_t>(slider->percentage * MAX_ARRAY_SIZE));
        } else {
            value = std::to_string(static_cast<size_t>(MAX_DELAY))
        }
    }
}

void Render::drawTrack(const Slider& slider) {
    rectangle.setFillColor(cold);

    const float thumbRadius = slider.thumb.size.x / 2.f;
    const float startOfTrack = slider.position.x + thumbRadius;
    
    const float thumbXPosition = slider.thumb.position.x;
    const float upToThumbWitdh = thumbXPosition - startOfTrack;
    
    rectangle.setPosition(slider.position);
    rectangle.setSize({upToThumbWitdh, slider.size.y});
    rectangle.setOrigin({0, slider.size.y / 2.f});
    
    window.draw(rectangle);
    
    const float endOfTrack = startOfTrack + slider.size.x - thumbRadius;
    const float thumbToEndWidth = endOfTrack - thumbXPosition;

    rectangle.setFillColor(hot);
    rectangle.setPosition({thumbXPosition, slider.position.y});
    rectangle.setSize({thumbToEndWidth, slider.size.y});
    rectangle.setOrigin({0, slider.size.y / 2.f});

    window.draw(rectangle);
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
    
    text.setFont(firaCodeFont);
    text.setCharacterSize(sortCycler.charSize);
    text.setLetterSpacing(1.f);
    setTextOrigin();
    
    text.setPosition(sortCycler.position);
    window.draw(text);
}

void Render::drawHUD(const HUD& hud, const VisualData& visualData) {
    rectangle.setFillColor(sf::Color(255, 255, 255, 40));
    rectangle.setSize(hud.area.size);
    rectangle.setPosition(hud.area.position);
    rectangle.setOrigin({0.f, 0.f});
    window.draw(rectangle);

    text.setFont(firaCodeFont);
    text.setCharacterSize(hud.charSize);
    text.setLetterSpacing(2.f);

    float xPosition = hud.initalPosition.x;
    float yPosition = hud.initalPosition.y;

    const float endOfArea = hud.area.position.x + hud.area.size.x - hud.padding;

    const size_t maxDigits = std::to_string(MAX_ARRAY_SIZE * MAX_ARRAY_SIZE).length();
    const std::string dummyZeros(maxDigits, '0');
    text.setString(dummyZeros);

    const float numberBlockWidth = text.getLocalBounds().size.x;
    const float staticNumberAnchorX = endOfArea - numberBlockWidth;

    const float lockedYOrigin = std::round(text.getLocalBounds().position.y + text.getLocalBounds().size.y / 2.f);
    
    auto setRightAlign = [&]() {
        const sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x, lockedYOrigin}); 
    };

    auto setLeftAlign = [&]() {
        const sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({0.f, lockedYOrigin});
    };
    
    auto drawLine = [&](const sf::String& name, const sf::String& stat, const bool isNumber = false) {
        text.setString(name);
        setLeftAlign();
        text.setPosition({xPosition, yPosition});
        window.draw(text);
        
        text.setString(stat);
        if (isNumber) {
            size_t numberOfZeroes = (maxDigits > stat.getSize()) ? (maxDigits - stat.getSize()) : 0;
            std::string zeroes(numberOfZeroes, '0');
            text.setString(zeroes);
            text.setFillColor(sf::Color(200, 200, 200));
            setLeftAlign();
            text.setPosition({staticNumberAnchorX, yPosition});
            window.draw(text);

            text.setString(zeroes + stat); 
            sf::Vector2f exactRedStartPos = text.findCharacterPos(numberOfZeroes);
            text.setString(stat);
            text.setOrigin({0.f, 0.f});
            text.setFillColor(sf::Color::Red);
            text.setPosition(exactRedStartPos); 
            window.draw(text);
        } else {
            text.setFillColor(getComplexityColor(stat));
            setRightAlign();
            text.setPosition({endOfArea, yPosition});
        }
        
        yPosition += hud.lineSpacing;
        window.draw(text);
        text.setFillColor(sf::Color::White);
    };

    drawLine("COMPARISONS", std::to_string(visualData.comparisons), true);
    drawLine("ARRAY ACCESSES", std::to_string(visualData.arrayAccesses), true);
    drawLine("TIME COMPLEXITY", hud.stats.timeComplexity);
    drawLine("WORST CASE", hud.stats.worstCase);
    drawLine("BEST CASE", hud.stats.bestCase);
    drawLine("SPACE COMPLEXITY", hud.stats.spaceComplexity);
}

sf::Color Render::getComplexityColor(const sf::String& complexity) {
    if (complexity == oOfOne or complexity == logN) {
        return sf::Color::Green; 
    } 
    else if (complexity == n or complexity == nLogN) {
        return sf::Color::Yellow; 
    } 
    else if (complexity == nSquared) {
        return sf::Color::Red; 
    }
    
    return sf::Color::White;
}

void Render::setTextOrigin() {
	const sf::FloatRect bounds = text.getLocalBounds();

	text.setOrigin({
		std::round(bounds.position.x + bounds.size.x / 2.f),
		std::round(bounds.position.y + bounds.size.y / 2.f)
	});
}