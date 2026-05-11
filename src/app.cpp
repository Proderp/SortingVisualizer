#include "app.hpp"

App::App() : 
    window(sf::VideoMode({DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}), "Sorting Visualizer"),
    windowSize(static_cast<sf::Vector2f>(window.getSize())),
    ui(window, windowSize, sortingEngine.getArray()),
    renderer(window, ui)
{
    updateArraySizeThumb();
}

void App::run() {
    while (window.isOpen()) {
        eventLoop();
        checkClock();
        render();
    }
}

void App::eventLoop() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const sf::Event::Resized* resizeEvent = event->getIf<sf::Event::Resized>()) {
            windowSize = static_cast<sf::Vector2f>(resizeEvent->size);
            ui.updateUI(sortingEngine.getArray());
        }

        if (const sf::Event::MouseButtonPressed* mousePressedEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressedEvent->button == sf::Mouse::Button::Left) {
                handleLeftClick(mousePressedEvent);
            } 
        }

        if (const sf::Event::MouseMoved* mouseMovedEvent = event->getIf<sf::Event::MouseMoved>()) {
            if (draggedSlider != ButtonType::None) {
                const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(mouseMovedEvent->position);
                handleSliderEvent(mousePosition);
            }
        }

        if (const sf::Event::MouseButtonReleased* mouseButtonReleeasedEvent = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseButtonReleeasedEvent->button == sf::Mouse::Button::Left) {
                draggedSlider = ButtonType::None;
            }
        }

        if (const sf::Event::KeyPressed* keyPressedEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressedEvent->scancode == sf::Keyboard::Scancode::Left) {
                isSorting = false;
                sortingEngine.runActionBackward();
                updateAnimationThumb();
            }

            if (keyPressedEvent->scancode == sf::Keyboard::Scancode::Right) {
                isSorting = false;
                sortingEngine.runActionForward();
                updateAnimationThumb();
            }

            if (keyPressedEvent->scancode == sf::Keyboard::Scancode::Space) {
                isSorting = !isSorting;
            }
            
            if (keyPressedEvent->scancode == sf::Keyboard::Scancode::R) {
                if (sortingEngine.getActionsSize() > 0) {
                    sortingEngine.scrubAnimation(0);
                    updateAnimationThumb();
                    isSorting = true;
                }
            }
        }
    }
}

void App::handleSliderEvent(const sf::Vector2f mousePosition) {
    std::optional<SliderEvent> event = ui.checkSliderClick(mousePosition, draggedSlider, sortingEngine.getActionsSize());

    if (event.has_value()) {

        if (event->id == ButtonType::AnimationSlider and sortingEngine.getActionsSize() == 0) {
            ui.resetAnimationSlider();
            draggedSlider = ButtonType::None; 
            return;
        }

        draggedSlider = event->id;

        switch (event->id) {
            case ButtonType::AnimationSlider: {
                isSorting = false;
                const Index targetIndex = static_cast<Index>(event->percentage * sortingEngine.getActionsSize());
                sortingEngine.scrubAnimation(targetIndex);
                break;
            }
            case ButtonType::ArraySizeSlider:
                const int potentialSize = static_cast<int>(500 * event->percentage);
                const int newArraySize = std::clamp(potentialSize, 10, 500);
                
                if (newArraySize == sortingEngine.getArraySize()) {
                    break;
                }
                
                stopSorting();
                sortingEngine.setArraySize(newArraySize);
                sortingEngine.randomizeArrayConsecutively();
                ui.updateUI(sortingEngine.getArray());
                break;
        }
    }
}

void App::handleLeftClick(const sf::Event::MouseButtonPressed* mousePressedEvent) {
    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(mousePressedEvent->position);
    const ButtonType clickedButton = ui.findClickedButton(mousePosition);

    switch (clickedButton) {
        using enum ButtonType;
        case Sort:
            stopSorting();
            sortingEngine.mergeWrapper();
            isSorting = true;
            break;
        case Randomize:
            stopSorting();
            sortingEngine.randomizeArray();
            ui.updateUI(sortingEngine.getArray());
            break;
        case Consecutive:
            stopSorting();
            sortingEngine.randomizeArrayConsecutively();
            ui.updateUI(sortingEngine.getArray());
            break;
        case None:
            break;
    }
    
    handleSliderEvent(mousePosition);
}

void App::stopSorting() {
    isSorting = false;
    sortingEngine.resetActions();
    sortingEngine.resetVisualData();
    ui.resetAnimationSlider();
}

void App::checkClock() {
    if (clock.getElapsedTime() >= interval and isSorting) {
        clock.restart();

        if (!sortingEngine.runActionForward()) {
            isSorting = false;
            return;
        }

        updateAnimationThumb();
    }
}

void App::updateAnimationThumb() {
    if (sortingEngine.getActionsSize() > 0) {
        float percentage = static_cast<float>(sortingEngine.getCurrentActionIndex()) / sortingEngine.getActionsSize();
        
        ui.setAnimationPercentage(percentage);
        ui.updateSliderLayout();
    }
}

void App::updateArraySizeThumb() {
    float percentage = static_cast<float>(sortingEngine.getArraySize() / 500);
    ui.setArraySizePercentage(percentage);
    ui.updateSliderLayout();
}

void App::render() {
    window.clear(sf::Color(25, 25, 28));

    renderer.drawArray(sortingEngine.getArray(), sortingEngine.getVisualData());
    renderer.drawButtonLayout(ui.getButtonLayout());
    renderer.drawSliderLayout(ui.getSliderLayout());

    window.display();
}