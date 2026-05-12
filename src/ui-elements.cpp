#include "ui-elements.hpp"

Button::Button(const std::string name, const ButtonType id) : name(name), id(id) {};

ButtonLayout::ButtonLayout() : 
    //sortButton("Sort", ButtonType::Sort),
    randomizeNormalButton("RANDOMIZE", ButtonType::Randomize),
    randomizeConsecutiveButton("CONSECUTIVE", ButtonType::Consecutive)
{}

Slider::Slider(const std::string buttonName, const ButtonType buttonID) :
    thumb(buttonName, buttonID)
{}

SliderLayout::SliderLayout() : 
    arraySizeSlider("ARRAY SIZE", ButtonType::ArraySizeSlider),
    latencySlider("SPEED", ButtonType::LatencySlider)
{}