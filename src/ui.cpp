#include "ui.hpp"

UI::UI(sf::RenderWindow& window, const sf::Vector2f& windowSize, const std::vector<Element>& array) :
    animationSlider("Steps", ButtonType::AnimationSlider),
    window(window),
    windowSize(windowSize)
{
    updateUI(array);
}

void UI::updateUI(const std::vector<Element>& array) {
    updateView();
    updateArrayDimensions(array);
    updateButtonLayout();
    updateSliderLayout();
}

void UI::updateView() {
    view.setSize(windowSize);

    const sf::Vector2f centerOfWindow = {windowSize.x / 2.f, windowSize.y / 2.f};
    view.setCenter(centerOfWindow);

    window.setView(view);
}

void UI::updateArrayDimensions(const std::vector<Element>& array) {
    arrayDimensions.offsetX = windowSize.x * 0.01f;
    arrayDimensions.offsetY = windowSize.y * 0.7f;

    if (array.empty()) {
        return;
    }

    const float allocatedBarArea = windowSize.x - arrayDimensions.offsetX * 2 - arrayDimensions.barSpacing * (array.size() - 1);
    arrayDimensions.barWidth = allocatedBarArea / array.size();

    const float distanceFromTop = windowSize.y * 0.02f;
    const float maxBarHeight = arrayDimensions.offsetY - distanceFromTop;
    
    auto maxElement = *std::max_element(array.begin(), array.end());
    arrayDimensions.barHeightUnit = maxBarHeight / maxElement;
}

void UI::updateButtonLayout() {
    const float columnBegin = arrayDimensions.offsetY + margin * 2.5f;
    const float columnHeight = windowSize.y - columnBegin;
    const float columnCenter = columnBegin + columnHeight / 2.f;
    
    const float buttonHeight = columnHeight / 2.f - margin;
    const float buttonWidth =  windowSize.x * 0.15f;
    
    const float xPosition = arrayDimensions.offsetX + buttonWidth / 2.f;
    sf::Vector2f position = {xPosition, columnBegin + buttonHeight / 2.f};
    buttonLayout.randomizeNormalButton.position = position;
    
    position = {xPosition, columnCenter + buttonHeight / 2.f};
    buttonLayout.randomizeConsecutiveButton.position = position;

    sf::Vector2f size = {buttonWidth, buttonHeight};
    buttonLayout.randomizeNormalButton.size = size;
    buttonLayout.randomizeConsecutiveButton.size = size;

    updateButtonBounds(buttonLayout.randomizeNormalButton);
    updateButtonBounds(buttonLayout.randomizeConsecutiveButton);

    buttonLayout.layoutWidth = arrayDimensions.offsetX + buttonWidth;

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
    buttonLayout.characterSize = buttonLayout.randomizeNormalButton.size.y / 4.f;
}

void UI::updateAnimationSlider() {
    const float xPosition = arrayDimensions.offsetX;
    const float yPosition = arrayDimensions.offsetY + margin;
    animationSlider.position = {xPosition, yPosition};

    const float trackWidth = windowSize.x - arrayDimensions.offsetX * 2.f;
    const float trackHeight = 4;
    animationSlider.size = {trackWidth, trackHeight};

    const float thumbRadius = trackHeight / 2.f;

    const sf::Vector2f middleLeftOfTrack = {xPosition, yPosition - thumbRadius};
    animationSlider.trackBounds = sf::FloatRect(middleLeftOfTrack, animationSlider.size);

    const float thumbHeight = trackHeight * 2.f;
    const float thumbWidth = thumbHeight * 3.f;
    animationSlider.thumb.size = {thumbWidth, thumbHeight};

    const float activeTrackWidth = trackWidth - thumbHeight;
    const float activeStartX = xPosition + (thumbHeight / 2.f);

    const float thumbXPosition = activeStartX + (activeTrackWidth * animationSlider.percentage);
    
    animationSlider.thumb.position = {thumbXPosition, yPosition};
    updateButtonBounds(animationSlider.thumb);
}

void UI::updateSliderLayout() {
    const float xPosition = buttonLayout.layoutWidth + margin;
    float sliderDistance = (windowSize.y - arrayDimensions.offsetY) / (sliderLayout.sliders.size() + 1);
    float startYPosition = arrayDimensions.offsetY + sliderDistance;
    
    const float trackHeight = 15;
    const float thumbRadius = trackHeight / 2.f;

    for (Index i{0}; i < sliderLayout.sliders.size(); i++) {
        Slider& slider = *sliderLayout.sliders.at(i);

        const float yPosition = startYPosition + sliderDistance * i;
        slider.position = {xPosition, yPosition};

        slider.size.y = trackHeight;
        
        float trackWidth = 200.f;
        slider.size = {trackWidth, trackHeight};

        const sf::Vector2f middleLeftOfTrack = {slider.position.x, slider.position.y - trackHeight / 2.f};
        slider.trackBounds = sf::FloatRect(middleLeftOfTrack, slider.size);
    
        slider.thumb.size = {trackHeight * 1.5f, trackHeight * 1.5f};

        const float minValue = xPosition + thumbRadius;
        const float maxValue = trackWidth - trackHeight;
        const float thumbXPosition = minValue + (maxValue * slider.percentage);
        
        slider.thumb.position = {thumbXPosition, yPosition};
        updateButtonBounds(slider.thumb);
    }

    updateAnimationSlider();
}

const ButtonType UI::findClickedButton(const sf::Vector2f mousePosition) {
    for (const Button* button : buttonLayout.buttons) {
        if (button->bounds.contains(mousePosition)) {
            return button->id;
        }
    }

    return ButtonType::None;
}

std::optional<SliderEvent> UI::checkSliderClick(const sf::Vector2f mousePosition, const ButtonType activeDragSlider, const uint16_t actionSize) {

    const bool isTimelineDragged = (activeDragSlider == animationSlider.thumb.id);
    const bool isInteracting = 
        animationSlider.thumb.bounds.contains(mousePosition) or 
        animationSlider.trackBounds.contains(mousePosition) or 
        isTimelineDragged;

    if (isInteracting) {
        return updateSliderPercentage(animationSlider, mousePosition.x);
    }

    for (Slider* slider : sliderLayout.sliders) {
        const bool isBeingDragged = (activeDragSlider == slider->thumb.id);
        const bool isInteracting = 
            slider->thumb.bounds.contains(mousePosition) or 
            slider->trackBounds.contains(mousePosition) or isBeingDragged;

        if (isInteracting) {
            return updateSliderPercentage(*slider, mousePosition.x);
        }
    }
    
    return std::nullopt;
}

SliderEvent UI::updateSliderPercentage(Slider& slider, const float mouseX) {
    const float trackStartX = slider.position.x;
    const float trackWidth = slider.size.x;
    const float thumbRadius = slider.thumb.size.x / 2.f;
    
    const float activeTrackWidth = trackWidth - slider.thumb.size.x;
    const float activeStartX = trackStartX + thumbRadius;

    const float relativeX = mouseX - activeStartX;    
    
    const float percentage = std::clamp(relativeX / activeTrackWidth, 0.0f, 1.0f);
    
    slider.percentage = percentage;
    updateSliderLayout();

    return SliderEvent{slider.thumb.id, percentage};
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

const SliderLayout& UI::getSliderLayout() const {
    return sliderLayout;
}

void UI::setAnimationPercentage(const float percentage) {
    animationSlider.percentage = std::clamp(percentage, 0.0f, 1.0f);
}

void UI::resetAnimationSlider() {
    setAnimationPercentage(0.f);
    updateSliderLayout();
}

void UI::setArraySizePercentage(const float percentage) {
    sliderLayout.sliders.at(0)->percentage = std::clamp(percentage, 0.0f, 1.0f);
}

void UI::setLatencyPercentage(const float percentage) {
    sliderLayout.sliders.at(1)->percentage = std::clamp(percentage, 0.0f, 1.0f);
}