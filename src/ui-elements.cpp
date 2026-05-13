#include "ui-elements.hpp"

Button::Button(const sf::String name, const ButtonType id) : name(name), id(id) {};

ButtonLayout::ButtonLayout() : 
    randomizeNormalButton("RANDOMIZE", ButtonType::Randomize),
    randomizeConsecutiveButton("CONSECUTIVE", ButtonType::Consecutive),
    stepBackButton(stepBackSymbol, ButtonType::StepBack),
    playButton(playSymbol, ButtonType::Play),
    stepForwardButton(stepForwardSymbol, ButtonType::StepForward)
{}

Slider::Slider(const sf::String buttonName, const ButtonType buttonID) :
    thumb(buttonName, buttonID)
{}

SliderLayout::SliderLayout() : 
    arraySizeSlider("ARRAY SIZE", ButtonType::ArraySizeSlider),
    latencySlider("SPEED", ButtonType::LatencySlider)
{}