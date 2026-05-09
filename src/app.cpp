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

        if (const sf::Event::KeyPressed* keyPressedEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressedEvent->scancode == sf::Keyboard::Scancode::Left) {
                isSorting = false;
                sortingEngine.runActionBackward();
            }

            if (keyPressedEvent->scancode == sf::Keyboard::Scancode::Right) {
                isSorting = false;
                sortingEngine.runActionForward();
            }

            if (keyPressedEvent->scancode == sf::Keyboard::Scancode::Space) {
                isSorting = !isSorting;
            }
        }
    }
}

void App::handleLeftClick(const sf::Event::MouseButtonPressed* mousePressedEvent) {
    const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(mousePressedEvent->position);
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
}

void App::stopSorting() {
    isSorting = false;
    sortingEngine.resetActions();
    sortingEngine.resetVisualData();
}

void App::checkClock() {
    if (clock.getElapsedTime() >= interval and isSorting) {
        clock.restart();

        if (!sortingEngine.runActionForward()) {
            isSorting = false;
            return;
        }

        /*
        Figure out where the thumb should be
        1. Find the currentActionIndex / actions.size()
        2. Find the pass this into updating the animation slider
        3. Get position by getting range of positions
        4. Multiply the ratio by the range
        5. Add the range to the starting x positions
        */
    }
}

void App::render() {
    window.clear(sf::Color(25, 25, 28));

    renderer.drawArray(sortingEngine.getArray(), sortingEngine.getVisualData());
    renderer.drawButtons(ui.getButtonLayout());
    renderer.drawAnimationSlider(ui.getAnimationSlider());

    window.display();
}