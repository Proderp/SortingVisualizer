#include "includes.hpp"

enum class ButtonType { Randomize, Consecutive, StepBack, Play, StepForward, AnimationSlider, ArraySizeSlider, DelaySlider, LeftArrow, RightArrow, None };

enum class DataType { Random, Consecutive };
enum class Algorithm { Bubble, Insertion, Merge, Quick, Count };
const std::array<sf::String, 4> algorithms = {"BUBBLE", "INSERTION", "MERGE", "QUICK"};

struct ArrayDimensions {
    float offsetX;
    float offsetY;

    float barWidth;
    float barHeightUnit;
    
    float barSpacing{0.f};
};

struct Button {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::FloatRect bounds;

    sf::String name;
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
    Slider delaySlider;

public:
    SliderLayout();

    const std::array<Slider*, 2> sliders = {&arraySizeSlider, &delaySlider};
    uint32_t characterSize{15};
};

struct SliderEvent {
    ButtonType id;
    float percentage;
};

struct SortCycler {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::FloatRect cyclingBounds;
    Algorithm algorithm;

    Button leftArrow;
    Button rightArrow;

    uint32_t charSize{20};

    SortCycler();
};

struct AlgorithmStats {
    sf::String timeComplexity;
    sf::String worstCase;
    sf::String bestCase;

    sf::String spaceComplexity;

    AlgorithmStats(sf::String time, sf::String worst, sf::String best, sf::String space);
};

struct HUD {
    sf::FloatRect area;
    sf::Vector2f initalPosition;
    float lineSpacing{25.f};
    float padding{15.f};
    uint32_t charSize{16};

    AlgorithmStats stats;

    HUD();
};
