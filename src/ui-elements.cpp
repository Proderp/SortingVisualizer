#include "ui-elements.hpp"

Button::Button(const std::string name, const ButtonType id) : name(name), id(id) {};

ButtonLayout::ButtonLayout() : 
    sortButton("Sort", ButtonType::Sort),
    randomizeNormalButton("Randomize", ButtonType::Randomize),
    randomizeConsecutiveButton("Consecutive", ButtonType::Consecutive)
{}

Slider::Slider(const std::string buttonName, const ButtonType buttonID) :
    thumb(buttonName, buttonID)
{}

SliderLayout::SliderLayout() : 
    animationSlider("Animation Slider", ButtonType::AnimationSlider),
    arraySizeSlider("Array Size", ButtonType::ArraySizeSlider),
    latencySlider("Speed", ButtonType::LatencySlider)
{}