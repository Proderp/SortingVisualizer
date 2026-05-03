#pragma once
#include "includes.hpp"
#include "render.hpp"
#include "sort-engine.hpp"
#include "ui.hpp"

class App {
private:
    sf::RenderWindow window;
    sf::Vector2f windowSize;

    UI ui;
    Render renderer;
    SortEngine sortingEngine;

    void eventLoop();
    
    void render();
public:

    App();

    void run();
};