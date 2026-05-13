#include "includes.hpp"

struct ArrayDimensions {
    float offsetX;
    float offsetY;

    float barWidth;
    float barHeightUnit;
    
    float barSpacing{0.f};
};

enum class ButtonType { Sort, Randomize, Consecutive, StepBack, Play, StepForward, AnimationSlider, ArraySizeSlider, LatencySlider, None };

struct Button {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::FloatRect bounds;

    const sf::String name;
    const ButtonType id;
    uint32_t charSize{30};

    Button(const sf::String name, const ButtonType id);
};

struct ButtonLayout {
    Button randomizeNormalButton;
    Button randomizeConsecutiveButton;
    Button stepBackButton;
    Button playButton;
    Button stepForwardButton;

    ButtonLayout();

    const std::array<Button*, 5> buttons = {&randomizeNormalButton, &randomizeConsecutiveButton, &stepBackButton, &playButton, &stepForwardButton};

    float layoutWidth;
};

struct Slider {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::FloatRect trackBounds;
    
    Button thumb;
    float percentage{0.f};
    
    Slider(const sf::String buttonName, const ButtonType buttonID);
};

struct SliderLayout {
private:
    Slider arraySizeSlider;
    Slider latencySlider;

public:
    SliderLayout();

    const std::array<Slider*, 2> sliders = {&arraySizeSlider, &latencySlider};
    uint32_t characterSize{15};
};

struct SliderEvent {
    ButtonType id;
    float percentage;
};