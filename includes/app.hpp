#pragma once
#include "includes.hpp"
#include "render.hpp"
#include "sort-engine.hpp"
#include "ui.hpp"

class App {
private:
    sf::RenderWindow window;

    Render renderer;
    SortEngine sortingEngine;

    sf::Vector2f windowSize;

    void eventLoop();
    
    void render();
public:

    App();

    void run();
};