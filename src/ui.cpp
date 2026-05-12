#include "ui.hpp"

UI::UI(sf::RenderWindow& window, const sf::Vector2f& windowSize, const std::vector<Element>& array) :
    animationSlider("Animation", ButtonType::AnimationSlider),
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
    const float xPosition = arrayDimensions.offsetX;
    const float yPosition = arrayDimensions.offsetY + margin;
    animationSlider.position = {xPosition, yPosition};

    const float trackWidth = windowSize.x - arrayDimensions.offsetX * 2.f;
    const float trackHeight = 15;
    animationSlider.size = {trackWidth, trackHeight};

    const float thumbRadius = trackHeight / 2.f;

    const sf::Vector2f middleLeftOfTrack = {xPosition, yPosition - thumbRadius};
    animationSlider.trackBounds = sf::FloatRect(middleLeftOfTrack, animationSlider.size);

    const float thumbSize = trackHeight * 1.5f;
    animationSlider.thumb.size = {thumbSize, thumbSize};

    const float activeTrackWidth = trackWidth - thumbSize;
    const float activeStartX = xPosition + (thumbSize / 2.f);

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
        
        float trackWidth;
        switch (slider.thumb.id) {
            // case ButtonType::AnimationSlider:
            //     trackWidth = windowSize.x - xPosition - arrayDimensions.offsetX;
            //     break;
            case ButtonType::ArraySizeSlider:
            case ButtonType::LatencySlider:
                trackWidth = 200.f;
                break;
        }

        slider.size = {trackWidth, trackHeight};

        const sf::Vector2f middleLeftOfTrack = {slider.position.x, slider.position.y - trackHeight / 2.f};
        slider.trackBounds = sf::FloatRect(middleLeftOfTrack, slider.size);
    
        slider.thumb.size = {trackHeight, trackHeight};

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
    
    if (animationSlider.thumb.bounds.contains(mousePosition) or 
        animationSlider.trackBounds.contains(mousePosition) or 
        isTimelineDragged) {
        
        const float trackStartX = animationSlider.position.x;
        const float trackWidth = animationSlider.size.x;
        const float thumbRadius = animationSlider.thumb.size.x / 2.f;
        
        const float activeTrackWidth = trackWidth - animationSlider.thumb.size.x;
        const float activeStartX = trackStartX + thumbRadius;

        const float relativeX = mousePosition.x - activeStartX;    
        
        float percentage = std::clamp(relativeX / activeTrackWidth, 0.0f, 1.0f);
        
        animationSlider.percentage = percentage;
        updateAnimationSlider();
        
        return SliderEvent{animationSlider.thumb.id, percentage};
    }

    for (Slider* slider : sliderLayout.sliders) {
        const bool isBeingDragged = (activeDragSlider == slider->thumb.id);

        if (slider->thumb.bounds.contains(mousePosition) or 
            slider->trackBounds.contains(mousePosition) or isBeingDragged) {
            const float trackStartX = slider->position.x;
            const float trackWidth = slider->size.x;
            const float thumbRadius = slider->thumb.size.x / 2.f;
            
            const float activeTrackWidth = trackWidth - slider->thumb.size.x;
            const float activeStartX = trackStartX + thumbRadius;

            const float relativeX = mousePosition.x - activeStartX;    
            
            const float percentage = std::clamp(relativeX / activeTrackWidth, 0.0f, 1.0f);
            
            slider->percentage = percentage;
            updateSliderLayout();

            return SliderEvent{slider->thumb.id, percentage};
        }
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