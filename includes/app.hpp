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

    void eventLoop();
    void handleLeftClick(const sf::Event::MouseButtonPressed* mousePressedEvent);
    
    void render();
public:

    App();

    void run();
};