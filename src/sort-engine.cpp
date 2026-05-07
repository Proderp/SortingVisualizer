#include "sort-engine.hpp"

Action::Action(ActionType action, Index indexOne, Index indexTwo) : 
    actionType(action),
    indexOne(indexOne), indexTwo(indexTwo)
{}

Action::Action(ActionType action, Index index) :
    actionType(action),
    indexOne(index)
{}

SortEngine::SortEngine() :
    twister(rd()),
    distribution(1, range)
{
    array.reserve(arraySize);
    randomizeArrayConsecutively();
}

void SortEngine::randomizeArray() {
    array.resize(arraySize);
    for (Index i{0}; i < arraySize; i++) {
        array.at(i) = distribution(twister);
    }
}

void SortEngine::randomizeArrayConsecutively() {
    array.resize(arraySize);
    std::iota(array.begin(), array.end(), 1);
    std::shuffle(array.begin(), array.end(), twister);
}

void SortEngine::bubbleSort() {
    std::vector<Element> newArray(array);

    for (Index i{0}; i < newArray.size(); i++) {
        Index sortedIndex = newArray.size() - i;
        bool swapMade{false};
        
        for (Index j{0}; j < sortedIndex - 1; j++) {
            actions.push_back(Action(ActionType::Compare, j, j + 1));
            if (newArray.at(j) > newArray.at(j + 1)) {
                actions.push_back(Action(ActionType::Swap, j, j + 1));
                
                std::swap(newArray.at(j), newArray.at(j + 1));
                swapMade = true;
            }
        }

        if (!swapMade) {
            for (Index k{0}; k < sortedIndex; k++) {
                actions.push_back(Action());
            }
            break;
        }

        actions.push_back(Action(ActionType::MarkSorted, sortedIndex - 1));
    }

    actions.push_back(Action());
}

bool SortEngine::runAction() {
    if (currentActionIndex >= actions.size()) {
        resetActions();
        return false;
    }
    
    const Action& action = actions.at(currentActionIndex);
    switch (action.actionType) {
        case ActionType::Compare:
            break;
        case ActionType::Swap:
            std::swap(array.at(action.indexOne.value()), array.at(action.indexTwo.value()));
            break;
    }

    currentActionIndex++;
    return true;
}

void SortEngine::resetActions() {
    actions.clear();
    currentActionIndex = 0;
}

const std::vector<Element>& SortEngine::getArray() const {
    return array;
}

const uint16_t SortEngine::getArraySize() const {
    return arraySize;
}