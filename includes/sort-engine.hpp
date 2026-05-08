#pragma once
#include "includes.hpp"

enum class ActionType {Compare, Swap, MarkSorted, Sorted};

struct Action {
    ActionType actionType;
    Index indexOne{INACTIVE}, indexTwo{INACTIVE};
    Element oldValue{INACTIVE}, newValue{INACTIVE};

    // Comparing and Swapping
    Action(ActionType action, Index indexOne, Index indexTwo);

    // Marking Sorted
    Action(ActionType action, Index index);

    // Merge Overwrite
    Action(ActionType action, Index index, Element oldValue, Element newValue);

    // Fully Sorted
    Action(ActionType action);
};

class SortEngine {
private:
    std::vector<Element> array;
    uint16_t arraySize{50};
    uint16_t range{100};

    std::random_device rd;
    std::mt19937 twister;
    std::uniform_int_distribution<> distribution;
    
    std::vector<Action> actions;
    Index currentActionIndex{0};
    VisualData visualData;

public:
    SortEngine();

    void randomizeArray();
    void randomizeArrayConsecutively();
    
    bool runAction();
    const VisualData& getVisualData() const;
    void resetActions();
    
    void resetVisualData();

    void bubbleSort();
    void mergeWrapper();
    void mergeSort(std::vector<Element>& tempArray, std::vector<Element>& originalArray, Index left, Index right);
    void merge(std::vector<Element>& tempArray, std::vector<Element>& originalArray, Index left, Index right);

    const std::vector<Element>& getArray() const;
    const uint16_t getArraySize() const;
};