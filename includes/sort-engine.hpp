#pragma once
#include "includes.hpp"

enum class ActionType {Compare, Swap, MarkSorted, Sorted};

struct Action {
    ActionType actionType;
    Index indexOne, indexTwo;

    // comparing and swapping
    Action(ActionType action, Index indexOne, Index indexTwo);

    // marking sorted
    Action(ActionType action, Index index);

    // fully sorted
    Action() : actionType(ActionType::Sorted) {}
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
public:
    SortEngine();

    void randomizeArray();
    void randomizeArrayConsecutively();

    const std::vector<Element>& getArray() const;
    const uint16_t getArraySize() const;

    void bubbleSort();
};