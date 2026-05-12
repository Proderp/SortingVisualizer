#include "includes.hpp"

struct ArrayDimensions {
    float offsetX;
    float offsetY;

    float barWidth;
    float barHeightUnit;
    
    float barSpacing{0.f};
};

enum class ButtonType { Sort, Randomize, Consecutive, AnimationSlider, ArraySizeSlider, LatencySlider, None };

struct Button {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::FloatRect bounds;

    const std::string name;
    const ButtonType id;

    Button(const std::string name, const ButtonType id);
};

struct ButtonLayout {
public:
    //Button sortButton;
    Button randomizeNormalButton;
    Button randomizeConsecutiveButton;

    ButtonLayout();

    const std::array<Button*, 2> buttons = {&randomizeNormalButton, &randomizeConsecutiveButton};

    float layoutWidth;
    uint32_t characterSize{30};
};

struct Slider {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::FloatRect trackBounds;
    
    Button thumb;
    float percentage{0.f};
    
    Slider(const std::string buttonName, const ButtonType buttonID);
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