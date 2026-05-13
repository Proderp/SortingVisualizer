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
    sf::Time latency{sf::milliseconds(0)};

    bool isSorting{false};
    ButtonType draggedSlider{ButtonType::None};

    void checkClock();
    void updateAnimationThumb();
    void updateArraySizeThumb(const SliderEvent& event);
    void updateLatencyThumb(const SliderEvent& event);
    void setArraySizeThumb();
    void setLatencyThumb();

    void eventLoop();
    void handleSliderEvent(const sf::Vector2f mousePosition);
    
    void handleLeftClick(const sf::Event::MouseButtonPressed* mousePressedEvent);
    void handlePlayButton();
    
    void handleKeyPressedEvent(const sf::Event::KeyPressed* keyPressedEvent);
    
    void stepButtonUpdate();
    void stepBack();
    void stepForward();

    void restartAnimation();
    
    void stopSorting();

    void updatePlayButtonSymbol();

    void render();
public:

    App();

    void run();
};