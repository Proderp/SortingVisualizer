#include "ui-elements.hpp"

const sf::String stepBack = L"\u23EE";
const sf::String play = L"\u25B6";
const sf::String stepForward = L"\u23ED";

Button::Button(const sf::String name, const ButtonType id) : name(name), id(id) {};

ButtonLayout::ButtonLayout() : 
    randomizeNormalButton("RANDOMIZE", ButtonType::Randomize),
    randomizeConsecutiveButton("CONSECUTIVE", ButtonType::Consecutive),
    stepBackButton(stepBack, ButtonType::StepBack),
    playButton(play, ButtonType::Play),
    stepForwardButton(stepForward, ButtonType::StepForward)
{}

Slider::Slider(const sf::String buttonName, const ButtonType buttonID) :
    thumb(buttonName, buttonID)
{}

SliderLayout::SliderLayout() : 
    arraySizeSlider("ARRAY SIZE", ButtonType::ArraySizeSlider),
    latencySlider("SPEED", ButtonType::LatencySlider)
{}