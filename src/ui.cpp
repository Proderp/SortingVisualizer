#include "ui.hpp"

UI::UI(sf::RenderWindow& window, const sf::Vector2f& windowSize, const std::vector<Element>& array) :
    animationSlider("Animation Slider", ButtonType::AnimationSlider),
    window(window),
    windowSize(windowSize)
{
    updateUI(array);
}

void UI::updateUI(const std::vector<Element>& array) {
    updateView();
    updateArrayDimensions(array);
    updateButtonLayout();
    updateAnimationSlider();
}

void UI::updateView() {
    view.setSize(windowSize);

    const sf::Vector2f centerOfWindow = {windowSize.x / 2.f, windowSize.y / 2.f};
    view.setCenter(centerOfWindow);

    window.setView(view);
}

void UI::updateArrayDimensions(const std::vector<Element>& array) {
    arrayDimensions.offsetX = windowSize.x * 0.1f;
    arrayDimensions.offsetY = windowSize.y * 0.7f;

    if (array.empty()) {
        return;
    }

    const float allocatedBarArea = windowSize.x - arrayDimensions.offsetX * 2 - arrayDimensions.barSpacing * (array.size() - 1);
    arrayDimensions.barWidth = allocatedBarArea / array.size();

    const float maxBarHeight = arrayDimensions.offsetY - (windowSize.y * 0.1f);
    auto maxElement = *std::max_element(array.begin(), array.end());
    arrayDimensions.barHeightUnit = maxBarHeight / maxElement;
}

void UI::updateButtonLayout() {
    const float xSize = (windowSize.y - arrayDimensions.offsetY) / 2.f;
    const sf::Vector2f size = {xSize, xSize / 2.f};
    
    const float yPosition = arrayDimensions.offsetY + xSize;
    float addedSpacing;
    
    for (Index i{0}; i < buttonLayout.buttons.size(); i++) {
        Button* button = buttonLayout.buttons.at(i);
        
        button->size = size;

        addedSpacing = xSize * (0.5f + i) + margin * i;
        button->position = {arrayDimensions.offsetX + addedSpacing, yPosition};
        
        updateButtonBounds(*button);
    }

    const Button& lastButton = *buttonLayout.buttons.at(2);
    buttonLayout.layoutWidth = lastButton.position.x + lastButton.size.x;

    updateCharacterSize();
}

void UI::updateButtonBounds(Button& button) {
    const sf::Vector2f topLeftCorner = {
        button.position.x - button.size.x / 2.f, 
        button.position.y - button.size.y / 2.f
    };
    
    button.bounds = sf::FloatRect(topLeftCorner, button.size);
}

void UI::updateCharacterSize() {
    buttonLayout.characterSize = buttonLayout.buttons.at(0)->size.y / 3;
}

void UI::updateAnimationSlider() {
    const float xPosition = buttonLayout.layoutWidth + margin;
    const float yPosition = windowSize.y * 0.85f;
    animationSlider.position = {xPosition, yPosition};

    const float height = 15;
    const float trackWidth = windowSize.x - xPosition - arrayDimensions.offsetX;
    animationSlider.size = {trackWidth, height};

    animationSlider.trackBounds = sf::FloatRect({animationSlider.position.x, animationSlider.position.y - height / 2.f}, animationSlider.size);

    Button& thumb = animationSlider.thumb;
    thumb.size = {height, height};
    
    const float thumbRadius = thumb.size.x / 2.f;
    const float minValue = xPosition + thumbRadius;
    const float maxValue = trackWidth - thumb.size.x;
    const float thumbXPosition = minValue + (maxValue * animationSlider.percentage);

    thumb.position = {thumbXPosition, yPosition};
    updateButtonBounds(thumb); 
}

const ButtonType UI::findClickedButton(const sf::Vector2f mousePosition) {
    for (const Button* button : buttonLayout.buttons) {
        if (button->bounds.contains(mousePosition)) {
            return button->id;
        }
    }

    return ButtonType::None;
}

std::optional<float> UI::checkSliderClick(const sf::Vector2f mousePosition) {
    
    if (animationSlider.thumb.bounds.contains(mousePosition) or 
        animationSlider.trackBounds.contains(mousePosition)) {
        
        const float trackStartX = animationSlider.position.x;
        const float trackWidth = animationSlider.size.x;
        const float thumbRadius = animationSlider.thumb.size.x / 2.f;

        const float activeTrackWidth = trackWidth - animationSlider.thumb.size.x;
        const float activeStartX = trackStartX + thumbRadius;

        const float relativeX = mousePosition.x - activeStartX;
        
        float percentage = std::clamp(relativeX / activeTrackWidth, 0.0f, 1.0f);
    
        setAnimationPercentage(percentage);
        updateAnimationSlider();
        
        return percentage;
    }
    
    return std::nullopt;
}

const ArrayDimensions& UI::getArrayDimensions() const {
    return arrayDimensions;
}

const ButtonLayout& UI::getButtonLayout() const {
    return buttonLayout;
}

const Slider& UI::getAnimationSlider() const {
    return animationSlider;
}

void UI::setAnimationPercentage(const float percentage) {
    animationSlider.percentage = percentage;
}