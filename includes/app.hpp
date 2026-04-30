#pragma once
#include "includes.hpp"
#include "render.hpp"

class App {
private:
    sf::RenderWindow window;
    sf::View view;

    Render renderer;

    sf::Vector2f windowSize;

    void eventLoop();
    void resetView();
    
    void render();
public:

    App();

    void run();
};