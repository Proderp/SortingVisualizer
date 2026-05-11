#include "sort-engine.hpp"

// Comparing and Swapping
Action::Action(ActionType action, Index indexOne, Index indexTwo) : 
    actionType(action),
    indexOne(indexOne), indexTwo(indexTwo)
{}

// Marking Sorted
Action::Action(ActionType action, Index index) :
    actionType(action),
    indexOne(index)
{}

// Overwrites
Action::Action(ActionType action, Index index, Element oldValue, Element newValue) : 
    actionType(action),
    indexOne(index),
    oldValue(oldValue), newValue(newValue)
{}

// Fully Sorted
Action::Action(ActionType action) : actionType(action) {}

SortEngine::SortEngine() :
    twister(rd()),
    distribution(1, range)
{
    visualData.sortedElements.resize(arraySize, false);

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
                actions.push_back(Action(ActionType::MarkSorted, k));
            }
            break;
        }

        actions.push_back(Action(ActionType::MarkSorted, sortedIndex - 1));
    }

    actions.push_back(Action(ActionType::Sorted));
}

void SortEngine::mergeWrapper() {
    if (array.empty()) {
        return;
    }

    std::vector<Element> tempArray(array);
    std::vector<Element> originalArray(array);
    
    Index left{0}, right{static_cast<Index>(arraySize - 1)};

    mergeSort(tempArray, originalArray, left, right);

    for (Index i{0}; i < arraySize; i++) {
        actions.push_back(Action(ActionType::MarkSorted, i));
    }
    actions.push_back(Action(ActionType::Sorted));
}

void SortEngine::mergeSort(std::vector<Element>& tempArray, std::vector<Element>& originalArray, const Index left, const Index right) {
    if (left >= right) {
        return;
    }

    Index middle{(left + right) / 2};

    mergeSort(tempArray, originalArray, left, middle);
    mergeSort(tempArray, originalArray, middle + 1, right);
    merge(tempArray, originalArray, left, middle, right);
}

void SortEngine::merge(std::vector<Element>& tempArray, std::vector<Element>& originalArray, const Index leftEnd, const Index middle, const Index rightEnd) {
    Index left{leftEnd}, right{middle + 1}, k{leftEnd};

    for (Index i{left}; i <= rightEnd; i++) {
        tempArray.at(i) = originalArray.at(i);
    }

    auto createOverwriteAction = [&](const Index index) {
        actions.push_back(Action(ActionType::Overwrite, k, originalArray.at(k), tempArray.at(index)));
    };

    while (left <= middle and right <= rightEnd) {

        actions.push_back(Action(ActionType::Compare, left, right));

        if (tempArray.at(left) < tempArray.at(right)) {
            createOverwriteAction(left);
            originalArray.at(k) = tempArray.at(left);
            left++;
        } else {
            createOverwriteAction(right);
            originalArray.at(k) = tempArray.at(right);
            right++;
        }
        
        k++;
    }

    while (left <= middle) {
        createOverwriteAction(left);
        originalArray.at(k) = tempArray.at(left);
        left++;        

        k++;
    }

    while (right <= rightEnd) {
        createOverwriteAction(right);
        originalArray.at(k) = tempArray.at(right);
        right++;
        
        k++;
    }
}

bool SortEngine::runActionForward() {
    if (currentActionIndex >= actions.size()) {
        return false;
    }
    
    const Action& action = actions.at(currentActionIndex);
    
    visualData.activeOne = INACTIVE;
    visualData.activeTwo = INACTIVE;
    visualData.isOverwrite = false;
    
    switch (action.actionType) {
        case ActionType::Compare:
            visualData.activeOne = action.indexOne;
            visualData.activeTwo = action.indexTwo;
            break;

        case ActionType::Swap:
            visualData.activeOne = action.indexOne;
            visualData.activeTwo = action.indexTwo;
            std::swap(array.at(action.indexOne), array.at(action.indexTwo));
            break;
        
        case ActionType::MarkSorted:
            visualData.activeOne = action.indexOne;
            visualData.sortedElements.at(action.indexOne) = true;
            break;
        
        case ActionType::Overwrite:
            visualData.isOverwrite = true;
            visualData.activeOne = action.indexOne;
            array.at(action.indexOne) = action.newValue;
            break;
        
        case ActionType::Sorted:
            visualData.isSorted = true;
            currentActionIndex++;
            return false;
            break;
    }

    currentActionIndex++;
    return true;
}

void SortEngine::runActionBackward() {
    if (currentActionIndex <= 0) {
        return;
    }

    currentActionIndex--;
    const Action& action = actions.at(currentActionIndex);

    if (currentActionIndex == 0) {
        visualData.activeOne = INACTIVE;
        visualData.activeTwo = INACTIVE;
    } else {
        visualData.activeOne = action.indexOne;
        visualData.activeTwo = action.indexTwo;
    }
    visualData.isOverwrite = false;

    switch (action.actionType) {
        case ActionType::Compare:
            // do nothing
            break;
        
        case ActionType::Swap:
            std::swap(array.at(action.indexOne), array.at(action.indexTwo));
            break;

        case ActionType::MarkSorted:
            visualData.sortedElements.at(action.indexOne) = false;
            visualData.isSorted = false;
            break;
        
        case ActionType::Overwrite:
            visualData.isOverwrite = true;
            array.at(action.indexOne) = action.oldValue;
            break;

        case ActionType::Sorted:
            visualData.isSorted = false;
            break;
    }
}

void SortEngine::scrubAnimation(const Index targetIndex) {
    const Index safeTargetIndex = std::clamp(targetIndex, static_cast<Index>(0), static_cast<Index>(getActionsSize()));

    // if the scrub went forward in time
    while (currentActionIndex < safeTargetIndex) {
        if (!runActionForward()) {
            break;
        }
    }

    // if the scrub went backward in time
    while (currentActionIndex > safeTargetIndex) {
        if (currentActionIndex == 0) {
            break;
        }
        runActionBackward();
    }
}

const VisualData& SortEngine::getVisualData() const {
    return visualData;
}

void SortEngine::resetActions() {
    actions.clear();
    currentActionIndex = 0;
}

void SortEngine::resetVisualData() {
    visualData = VisualData{};
    visualData.sortedElements.resize(arraySize, false);
}

const std::vector<Element>& SortEngine::getArray() const {
    return array;
}

const uint16_t SortEngine::getArraySize() const {
    return arraySize;
}

const uint16_t SortEngine::getActionsSize() const {
    return actions.size();
}

const Index SortEngine::getCurrentActionIndex() const {
    return currentActionIndex;
}

void SortEngine::setArraySize(const uint16_t newArraySize) {
    arraySize = newArraySize;
}