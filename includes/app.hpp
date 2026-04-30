#pragma once
#include "includes.hpp"

class App {
private:
    sf::RenderWindow window;
    sf::View view;

    sf::Vector2f windowSize;

    void eventLoop();
    void resetView();
    
    void render();
public:

    App();

    void run();
};