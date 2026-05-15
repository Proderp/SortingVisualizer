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
    sf::Time delay{sf::milliseconds(0)};

    bool isSorting{false};
    ButtonType draggedSlider{ButtonType::None};

    Algorithm algorithm{Algorithm::Bubble};
    DataType dataType{DataType::Consecutive};

    void checkClock();
    void updateAnimationThumb();
    void updateArraySizeThumb(const SliderEvent& event);
    void updateDelayThumb(const SliderEvent& event);
    void setArraySizeThumb();
    void setDelayThumb();

    void eventLoop();
    void handleSliderEvent(const sf::Vector2f mousePosition);
    
    void handleLeftClick(const sf::Event::MouseButtonPressed* mousePressedEvent);
    void handlePlayButton();
    
    void handleKeyPressedEvent(const sf::Event::KeyPressed* keyPressedEvent);

    void stepButtonUpdate();
    void stepBack();
    void stepForward();

    void cycleAlgorithms(const bool scrolledUp);
    void getNextAlgorithm();
    void getPreviousAlgorithm();
    void handleSwitchedAlgorithm();

    void restartAnimation();
    
    void startSorting();
    void stopSorting();

    void updatePlayButtonSymbol();

    void render();
public:

    App();

    void run();
};