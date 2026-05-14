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

struct VisualData {
    Index activeOne{INACTIVE}, activeTwo{INACTIVE};
    Index pivot{INACTIVE};
    bool isOverwrite{false};

    bool isSorted{false};
    std::vector<bool> sortedElements; 

    size_t comparisons{0};
    size_t arrayAccesses{0};
};

class SortEngine {
private:
    std::vector<Element> baseArray;
    std::vector<Element> array;
    size_t arraySize{500};
    uint16_t range{500};

    std::random_device rd;
    std::mt19937 twister;
    std::uniform_int_distribution<> distribution;
    
    std::vector<Action> actions;
    size_t currentActionIndex{0};
    size_t currentPivot{INACTIVE};
    VisualData visualData;

    bool isArraySorted(const std::vector<Element>& tempArray);
    void createCoolAnimation();

    void mergeSort(std::vector<Element>& tempArray, std::vector<Element>& originalArray, const Index left, const Index right);
    void merge(std::vector<Element>& tempArray, std::vector<Element>& originalArray, const Index leftEnd, const Index middle, const Index rightEnd);

    void quickSort(std::vector<Element>& tempArray, const Index rightEnd, const Index leftEnd);
public:
    SortEngine();

    void copyBaseArray();

    void randomizeArray();
    void randomizeArrayConsecutively();
    
    bool runActionForward();
    void runActionBackward();
    void scrubAnimation(const Index targetIndex);
    const VisualData& getVisualData() const;
    void resetActions();
    
    void resetVisualData();

    void bubbleSort();

    void insertionSort();

    void mergeSortWrapper();

    void quickSortWrapper();

    const std::vector<Element>& getArray() const;
    const size_t getArraySize() const;
    const size_t getActionsSize() const;
    const size_t getCurrentActionIndex() const;
    const bool isActionsEmpty() const;

    void setArraySize(const size_t newArraySize);
};