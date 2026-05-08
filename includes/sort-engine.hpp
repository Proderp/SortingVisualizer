#pragma once
#include "includes.hpp"

enum class ActionType {Compare, Swap, MarkSorted, Overwrite, Sorted};

struct Action {
    ActionType actionType;
    Index indexOne{INACTIVE}, indexTwo{INACTIVE};
    Element oldValue{INACTIVE}, newValue{INACTIVE};

    // Comparing and Swapping
    Action(ActionType action, Index indexOne, Index indexTwo);

    // Marking Sorted
    Action(ActionType action, Index index);

    // Overwrite
    Action(ActionType action, Index index, Element oldValue, Element newValue);

    // Fully Sorted
    Action(ActionType action);
};

class SortEngine {
private:
    std::vector<Element> array;
    uint16_t arraySize{300};
    uint16_t range{100};

    std::random_device rd;
    std::mt19937 twister;
    std::uniform_int_distribution<> distribution;
    
    std::vector<Action> actions;
    Index currentActionIndex{0};
    VisualData visualData;

    void mergeSort(std::vector<Element>& tempArray, std::vector<Element>& originalArray, const Index left, const Index right);
    void merge(std::vector<Element>& tempArray, std::vector<Element>& originalArray, const Index leftEnd, const Index middle, const Index rightEnd);

public:
    SortEngine();

    void randomizeArray();
    void randomizeArrayConsecutively();
    
    bool runActionForward();
    void runActionBackward();
    const VisualData& getVisualData() const;
    void resetActions();
    
    void resetVisualData();

    void bubbleSort();

    void mergeWrapper();

    const std::vector<Element>& getArray() const;
    const uint16_t getArraySize() const;
};