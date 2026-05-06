#pragma once
#include "includes.hpp"
#include "render.hpp"
#include "sort-engine.hpp"
#include "ui.hpp"

class App {
private:
    sf::RenderWindow window;
    sf::Vector2f windowSize;

    SortEngine sortingEngine;
    UI ui;
    Render renderer;

    sf::Clock clock;
    sf::Time interval = sf::milliseconds(500);

    void checkClock();

    void eventLoop();
    void handleLeftClick(const sf::Event::MouseButtonPressed* mousePressedEvent);
    
    void render();
public:

    App();

    void run();
};