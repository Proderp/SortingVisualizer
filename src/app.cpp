#include "app.hpp"

App::App() : 
    window(sf::VideoMode({DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}), "Sorting Visualizer"),
    windowSize(static_cast<sf::Vector2f>(window.getSize())),
    ui(window, windowSize, sortingEngine.getArray()),
    renderer(window, ui)
{}

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
            if (isDragging and sortingEngine.getActionsSize() > 0) {
                const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(mouseMovedEvent->position);
                std::optional<float> percentage = ui.checkSliderClick(mousePosition, isDragging);

                if (percentage.has_value()) {
                    Index targetIndex = static_cast<Index>(percentage.value() * sortingEngine.getActionsSize());
                    sortingEngine.scrubAnimation(targetIndex);
                }
            }
        }

        if (const sf::Event::MouseButtonReleased* mouseButtonReleeasedEvent = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseButtonReleeasedEvent->button == sf::Mouse::Button::Left) {
                isDragging = false;
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

    if (sortingEngine.getActionsSize() > 0) {
        findNewPercentage();
    }    
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
        ui.updateAnimationSlider();
    }
}

void App::findNewPercentage() {
    const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    std::optional<float> percentage = ui.checkSliderClick(mousePosition, isDragging);

    if (percentage.has_value()) {
        isDragging = true;
        isSorting = false;

        Index targetIndex = static_cast<Index>(percentage.value() * sortingEngine.getActionsSize());
        sortingEngine.scrubAnimation(targetIndex);
    }
}

void App::render() {
    window.clear(sf::Color(25, 25, 28));

    renderer.drawArray(sortingEngine.getArray(), sortingEngine.getVisualData());
    renderer.drawButtons(ui.getButtonLayout());
    renderer.drawAnimationSlider(ui.getAnimationSlider());

    window.display();
}