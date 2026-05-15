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
    updateSortCycler();
    updateHUD();
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
    updateRandomizeButtons();
    updateControlButtons();

    updateCharacterSize();
}

void UI::updateRandomizeButtons() {
    const float rowBegin = arrayDimensions.offsetY + margin * 2.f;
    const float rowHeight = windowSize.y - rowBegin;
    const float rowCenter = rowBegin + rowHeight / 2.f;
    
    const float buttonHeight = rowHeight / 2.f - margin;
    const float buttonWidth =  windowSize.x * 0.15f;
    
    const float xPosition = arrayDimensions.offsetX + buttonWidth / 2.f;
    sf::Vector2f position = {xPosition, rowBegin + buttonHeight / 2.f};
    buttonLayout.randomizeNormalButton.position = position;
    
    position = {xPosition, rowCenter + buttonHeight / 2.f};
    buttonLayout.randomizeConsecutiveButton.position = position;

    sf::Vector2f size = {buttonWidth, buttonHeight};
    buttonLayout.randomizeNormalButton.size = size;
    buttonLayout.randomizeConsecutiveButton.size = size;

    updateButtonBounds(buttonLayout.randomizeNormalButton);
    updateButtonBounds(buttonLayout.randomizeConsecutiveButton);

    buttonLayout.layoutWidth = arrayDimensions.offsetX + buttonWidth;
}

void UI::updateControlButtons() {
    const float columnBegin = windowSize.x * 0.35f;
    const float columnWidth = windowSize.x * 0.3f;
    const float columnCenter = columnBegin + columnWidth / 2.f;

    const float rowBegin = arrayDimensions.offsetY + margin * 1.75f;
    const float rowHeight = windowSize.y - rowBegin - margin;
    const float rowCenter = rowBegin + rowHeight / 2.f;

    const float allocatedWidth = columnWidth - margin * 2.f;

    const float width = allocatedWidth * 0.4f;
    buttonLayout.playButton.size = {width, width};
    buttonLayout.playButton.position = {columnCenter, rowCenter};
    updateButtonBounds(buttonLayout.playButton);

    const float smallerWidth = width / 2.f;
    buttonLayout.stepBackButton.size = {smallerWidth, smallerWidth};
    buttonLayout.stepForwardButton.size = {smallerWidth, smallerWidth};

    const float stepBackPositionX = columnBegin + smallerWidth / 2.f + margin * 1.5f;
    buttonLayout.stepBackButton.position = {stepBackPositionX, rowCenter};
    updateButtonBounds(buttonLayout.stepBackButton);

    const float stepForwardPositionX = columnBegin + columnWidth - smallerWidth / 2.f - margin * 1.5f;
    buttonLayout.stepForwardButton.position = {stepForwardPositionX, rowCenter};
    updateButtonBounds(buttonLayout.stepForwardButton);
}

void UI::updateButtonBounds(Button& button) {
    const sf::Vector2f topLeftCorner = {
        button.position.x - button.size.x / 2.f, 
        button.position.y - button.size.y / 2.f
    };
    
    button.bounds = sf::FloatRect(topLeftCorner, button.size);
}

void UI::updateCharacterSize() {
    for (Button* button : buttonLayout.buttons) {
        if (button->id == ButtonType::Play or 
            button->id == ButtonType::StepBack or 
            button->id == ButtonType::StepForward) {

            button->charSize = button->size.x * 0.6f;
        } else {
            button->charSize = button->size.x * 0.07f;
        }
    }
}

void UI::updateAnimationSlider() {
    const float xPosition = arrayDimensions.offsetX;
    const float yPosition = arrayDimensions.offsetY + margin;
    animationSlider.position = {xPosition, yPosition};

    const float trackWidth = windowSize.x - arrayDimensions.offsetX * 2.f;
    const float trackHeight = 4;
    animationSlider.size = {trackWidth, trackHeight};

    const float thumbHeight = 20.f;
    const float thumbWidth = 12.f;
    animationSlider.thumb.size = {thumbWidth, thumbHeight};
    
    const float thumbRadius = thumbWidth / 2.f;
    
    const float activeStartX = xPosition + thumbRadius;
    const float activeEndX = trackWidth - thumbWidth;
    
    const float thumbXPosition = activeStartX + (activeEndX * animationSlider.percentage);
    
    animationSlider.thumb.position = {thumbXPosition, yPosition};
    updateButtonBounds(animationSlider.thumb);

    const sf::Vector2f middleLeftOfTrack = {xPosition, yPosition - trackHeight / 2.f};
    animationSlider.trackBounds = sf::FloatRect(middleLeftOfTrack, animationSlider.size);
}

void UI::updateSliderLayout() {
    const float columnBegin = buttonLayout.stepForwardButton.position.x + buttonLayout.stepForwardButton.size.x + margin;
    const float columnWidth = windowSize.x - arrayDimensions.offsetX - columnBegin;

    const float rowBegin = arrayDimensions.offsetY + margin * 1.75f;
    const float rowHeight = windowSize.y - rowBegin - margin;
    
    const float thumbWidth = 10.f;
    const float thumbHeight = 16.f;
    const float thumbRadius = thumbWidth / 2.f;

    const float trackHeight = 2.f;
    const float trackWidth = columnWidth;
    
    const float dynamicFontSize = windowSize.y * 0.0175f;
    sliderLayout.characterSize = static_cast<uint32_t>(std::clamp(dynamicFontSize, 15.f, 30.f));
    
    const float sliderSpacing = rowHeight / 3.f + dynamicFontSize / 2.f;
    float yPosition = rowBegin + sliderSpacing;

    for (Index i{0}; i < sliderLayout.sliders.size(); i++) {
        Slider& slider = *sliderLayout.sliders.at(i);

        yPosition += i * sliderSpacing;
        slider.position = {columnBegin, yPosition};

        slider.size = {trackWidth, trackHeight};
        sf::Vector2f middleLeftOfTrack = {columnBegin, yPosition - trackHeight / 2.f};
        slider.trackBounds = sf::FloatRect(middleLeftOfTrack, slider.size);

        slider.thumb.size = {thumbWidth, thumbHeight};

        const float activeStartX = columnBegin + thumbRadius;
        const float activeEndX = trackWidth - thumbWidth;
        const float thumbXPosition = activeStartX + (activeEndX * slider.percentage);
        
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

    if (sortCycler.leftArrow.bounds.contains(mousePosition)) {
        return sortCycler.leftArrow.id;
    } 

    if (sortCycler.rightArrow.bounds.contains(mousePosition)) {
        return sortCycler.rightArrow.id;
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

void UI::updateSortCycler() {
    const float columnBegin = buttonLayout.layoutWidth + margin;
    const float columnWidth = windowSize.x - columnBegin - buttonLayout.stepForwardButton.position.x - buttonLayout.stepForwardButton.size.x / 2.f - margin;
    const float columnCenter = columnBegin + columnWidth / 2.f;
    
    const float rowBegin = arrayDimensions.offsetY + margin * 1.75f;
    const float rowHeight = windowSize.y - rowBegin - margin;
    const float rowCenter = rowBegin + rowHeight / 2.f;

    sf::Vector2f boundsPosition = {columnBegin, rowBegin};
    sf::Vector2f boundsSize = {columnWidth, rowHeight};
    sortCycler.cyclingBounds = sf::FloatRect(boundsPosition, boundsSize);

    sortCycler.position = {columnCenter, rowCenter};

    const float width = columnWidth / 1.5f;
    const float height = rowHeight / 3.f;
    sortCycler.size = {width, height};

    const float buttonWidth = (columnWidth - width) / 2.f;
    const sf::Vector2f buttonSize = {buttonWidth, height};
    sortCycler.leftArrow.size = buttonSize;
    sortCycler.rightArrow.size = buttonSize;

    const float buttonYPosition = rowCenter;

    const float buttonRadius = buttonSize.x / 2.f;
    const float leftXPosition = columnBegin + buttonRadius;
    const float rightXPosition = columnBegin + columnWidth - buttonRadius;

    sortCycler.leftArrow.position = {leftXPosition, buttonYPosition};
    sortCycler.rightArrow.position = {rightXPosition, buttonYPosition};

    updateButtonBounds(sortCycler.leftArrow);
    updateButtonBounds(sortCycler.rightArrow);

    sortCycler.charSize = height / 2.5f;
}

void UI::updateHUD() {
    const float dynamicFontSize = windowSize.y * 0.015f;
    hud.charSize = static_cast<uint32_t>(std::clamp(dynamicFontSize, 12.f, 24.f));
    
    hud.lineSpacing = hud.charSize * 2.f;
    
    const float absoluteMinWidth = 280.f;
    const float hudWidth = std::max(windowSize.x * 0.20f, absoluteMinWidth);
    const float hudHeight = hud.lineSpacing * 6.f + hud.padding * 2.f;
    
    const sf::Vector2f hudSize = {hudWidth, hudHeight};
    const sf::Vector2f hudPosition = {arrayDimensions.offsetX, arrayDimensions.offsetX};
    
    hud.area = sf::FloatRect(hudPosition, hudSize);

    hud.initalPosition = {hudPosition.x + hud.padding, hudPosition.y + hud.lineSpacing / 2.f + hud.padding};
}

void UI::updateHUDStats(const Algorithm algorithm) {
    switch (algorithm) {
        using enum Algorithm;
        case Bubble:
            setHUDStats(AlgorithmStats(nSquared, nSquared, n, oOfOne));
            break;
        case Insertion:
            setHUDStats(AlgorithmStats(nSquared, nSquared, n, oOfOne));
            break;
        case Merge:
            setHUDStats(AlgorithmStats(nLogN, nLogN, nLogN, n));
            break;
        case Quick:
            setHUDStats(AlgorithmStats(nLogN, nSquared, nLogN, logN));
            break;
    }
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

const SortCycler& UI::getSortCycler() const {
    return sortCycler;
}

const HUD& UI::getHUD() const {
    return hud;
}

void UI::setAnimationPercentage(const float percentage) {
    animationSlider.percentage = std::clamp(percentage, 0.0f, 1.0f);
}

void UI::resetAnimationSlider() {
    setAnimationPercentage(0.f);
    updateSliderLayout();
}

void UI::setArraySizePercentage(const float percentage) {
    Slider& arraySizeSlider = *sliderLayout.sliders.at(0); 
    arraySizeSlider.percentage = std::clamp(percentage, 0.0f, 1.0f);
}

void UI::setDelayPercentage(const float percentage) {
    Slider& delaySlider = *sliderLayout.sliders.at(1);
    delaySlider.percentage = std::clamp(percentage, 0.0f, 1.0f);
}

void UI::setPlayButtonSymbol(const sf::String newSymbol) {
    buttonLayout.playButton.name = newSymbol;
}

void UI::setSortCycleAlgorithm(const Algorithm algorithm) {
    sortCycler.algorithm = algorithm;
}

void UI::setHUDStats(AlgorithmStats stats) {
    hud.stats = stats;
}