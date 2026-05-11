#pragma once
#include "includes.hpp"

enum class ActionType {Compare, Swap, MarkSorted, Overwrite, SetPivot, Sorted};

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
    uint16_t arraySize{MAX_ARRAY_SIZE};
    uint16_t range{500};

    std::random_device rd;
    std::mt19937 twister;
    std::uniform_int_distribution<> distribution;
    
    std::vector<Action> actions;
    Index currentActionIndex{0};
    Index currentPivot{INACTIVE};
    VisualData visualData;

    void mergeSort(std::vector<Element>& tempArray, std::vector<Element>& originalArray, const Index left, const Index right);
    void merge(std::vector<Element>& tempArray, std::vector<Element>& originalArray, const Index leftEnd, const Index middle, const Index rightEnd);

public:
    SortEngine();

    void randomizeArray();
    void randomizeArrayConsecutively();
    
    bool runActionForward();
    void runActionBackward();
    void scrubAnimation(const Index targetIndex);
    const VisualData& getVisualData() const;
    void resetActions();
    
    void resetVisualData();

    void bubbleSort();

    void mergeSortWrapper();

    void quickSortWrapper();
    void quickSort(std::vector<Element>& tempArray, const Index rightEnd, const Index leftEnd);

    const std::vector<Element>& getArray() const;
    const uint16_t getArraySize() const;
    const uint16_t getActionsSize() const;
    const Index getCurrentActionIndex() const;

    void setArraySize(const uint16_t newArraySize);
};