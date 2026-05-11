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
    sf::Time interval{sf::milliseconds(1)};

    bool isSorting{false};
    ButtonType draggedSlider{ButtonType::None};

    void checkClock();
    void updateAnimationThumb();
    void updateArraySizeThumb();

    void eventLoop();
    void handleSliderEvent(const sf::Vector2f mousePosition);
    void handleLeftClick(const sf::Event::MouseButtonPressed* mousePressedEvent);
    
    void stopSorting();

    void render();
public:

    App();

    void run();
};