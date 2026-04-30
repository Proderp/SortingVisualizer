#pragma once
#include "includes.hpp"
#include "render.hpp"
#include "sort-engine.hpp"
#include "ui.hpp"

class App {
private:
    sf::RenderWindow window;
    sf::Vector2f windowSize;

    Render renderer;
    SortEngine sortingEngine;
    UI ui;

    void eventLoop();
    
    void render();
public:

    App();

    void run();
};