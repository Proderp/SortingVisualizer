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
    delaySlider("DELAY", ButtonType::DelaySlider)
{}

SortCycler::SortCycler() :
    leftArrow(leftSymbol, ButtonType::LeftArrow),
    rightArrow(rightSymbol, ButtonType::RightArrow)
{}

AlgorithmStats::AlgorithmStats(sf::String time, sf::String worst, sf::String best, sf::String space) :
    timeComplexity(time),
    worstCase(worst),
    bestCase(best),
    spaceComplexity(space)
{}

HUD::HUD() :
    stats(nSquared, nSquared, n, oOfOne)
{}