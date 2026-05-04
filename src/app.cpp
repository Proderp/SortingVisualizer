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
    }
}

void App::render() {
    window.clear(sf::Color(25, 25, 28));

    renderer.drawArray(sortingEngine.getArray());
    renderer.drawButtons(ui.getButtonLayout());

    window.display();
}