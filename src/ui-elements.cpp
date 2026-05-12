#include "ui-elements.hpp"

Button::Button(const std::string name, const ButtonType id) : name(name), id(id) {};

ButtonLayout::ButtonLayout() : 
    randomizeNormalButton("RANDOMIZE", ButtonType::Randomize),
    randomizeConsecutiveButton("CONSECUTIVE", ButtonType::Consecutive),
    stepBackButton("⏮", ButtonType::StepBack),
    playButton("▶", ButtonType::Play),
    stepForwardButton("⏭", ButtonType::StepForward)
{}

Slider::Slider(const std::string buttonName, const ButtonType buttonID) :
    thumb(buttonName, buttonID)
{}

SliderLayout::SliderLayout() : 
    arraySizeSlider("ARRAY SIZE", ButtonType::ArraySizeSlider),
    latencySlider("SPEED", ButtonType::LatencySlider)
{}