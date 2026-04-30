#include "app.hpp"

App::App() : 
    window(sf::VideoMode({DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}), "Sorting Visualizer"),
    renderer(window),
    windowSize(static_cast<sf::Vector2f>(window.getSize()))
{
    resetView();
}

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
            resetView();
        }
    }
}

void App::resetView() {
    view.setSize(windowSize);
    view.setCenter({windowSize.x / 2.f, windowSize.y / 2.f});

    window.setView(view);
}

void App::render() {
    window.clear(sf::Color(25, 25, 28));

    window.display();
}