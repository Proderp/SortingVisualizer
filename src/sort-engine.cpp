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

void SortEngine::copyBaseArray() {
    array = baseArray;
}

void SortEngine::randomizeArray() {
    baseArray.resize(arraySize);
    for (Index i{0}; i < arraySize; i++) {
        baseArray.at(i) = distribution(twister);
    }
    array = baseArray;
}

void SortEngine::randomizeArrayConsecutively() {
    baseArray.resize(arraySize);
    std::iota(baseArray.begin(), baseArray.end(), 1);
    std::shuffle(baseArray.begin(), baseArray.end(), twister);
    array = baseArray;
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

bool SortEngine::isArraySorted(const std::vector<Element>& tempArray) {
    for (Index i{0}; i < arraySize - 1; i++) {
        if (tempArray.at(i) > tempArray.at(i + 1)) {
            return false;
        }
    }

    return true;
}

void SortEngine::createCoolAnimation() {
    for (Index i{0}; i < arraySize; i++) {
        actions.push_back(Action(ActionType::MarkSorted, i));
    }
    actions.push_back(Action(ActionType::Sorted));
}

void SortEngine::mergeSortWrapper() {
    std::vector<Element> tempArray(array);
    std::vector<Element> originalArray(array);
    
    const Index left{0}, right{static_cast<Index>(arraySize - 1)};

    if (isArraySorted(tempArray)) {
        createCoolAnimation();
        return;
    }

    mergeSort(tempArray, originalArray, left, right);
    createCoolAnimation();
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

void SortEngine::quickSortWrapper() {
    const Index leftEnd{0};
    const Index rightEnd{static_cast<Index>(arraySize - 1)};

    std::vector<Element> tempArray(array);

    if (isArraySorted(tempArray)) {
        createCoolAnimation();   
        return;
    }

    quickSort(tempArray, leftEnd, rightEnd);
    actions.push_back(Action(ActionType::SetPivot, INACTIVE, currentPivot));
    currentPivot = INACTIVE;
    actions.push_back(Action(ActionType::Sorted));
}

void SortEngine::quickSort(std::vector<Element>& tempArray, const Index leftEnd, const Index rightEnd) {
    if (leftEnd >= rightEnd) {
        actions.push_back(Action(ActionType::MarkSorted, leftEnd));
        return;
    }

    Index pivot = rightEnd;
    actions.push_back(Action(ActionType::SetPivot, pivot, currentPivot));
    currentPivot = pivot;

    Index leftPointer{leftEnd}, rightPointer{static_cast<Index>(rightEnd)};

    while (true) {
        for (; leftPointer < rightEnd; leftPointer++) {
            actions.push_back(Action(ActionType::Compare, leftPointer, pivot));
            if (tempArray.at(leftPointer) > tempArray.at(pivot)) {
                break;
            }
        }
        
        for (; rightPointer > leftEnd; rightPointer--) {
            actions.push_back(Action(ActionType::Compare, rightPointer, pivot));
            if (tempArray.at(rightPointer) < tempArray.at(pivot)) {
                break;
            }
        }

        actions.push_back(Action(ActionType::Compare, leftPointer, rightPointer));
        if (leftPointer < rightPointer) {
            actions.push_back(Action(ActionType::Swap, leftPointer, rightPointer));
            std::swap(tempArray.at(leftPointer), tempArray.at(rightPointer));
        } else {
            break;
        }
    }

    actions.push_back(Action(ActionType::Swap, leftPointer, pivot));
    std::swap(tempArray.at(leftPointer), tempArray.at(pivot));
    actions.push_back(Action(ActionType::MarkSorted, leftPointer));

    actions.push_back(Action(ActionType::Compare, leftPointer, leftEnd));
    if (leftPointer > leftEnd) {
        quickSort(tempArray, leftEnd, leftPointer - 1);
    }

    actions.push_back(Action(ActionType::Compare, leftPointer, rightEnd));
    if (leftPointer < rightEnd) {
        quickSort(tempArray, leftPointer + 1, rightEnd);
    } 
}

void SortEngine::insertionSort() {
    std::vector<Element> tempArray(array);

    for (Index i{1}; i < arraySize; i++) {
        int j = i - 1;

        while (j >= 0) {
            actions.push_back(Action(ActionType::Compare, j, j + 1));
            if (tempArray.at(j + 1) < tempArray.at(j)) {
                actions.push_back(Action(ActionType::Swap, j, j + 1));
                std::swap(tempArray.at(j), tempArray.at(j + 1));            
                j--;
            } else {
                break;
            }
        }
    }

    createCoolAnimation();
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

        case ActionType::SetPivot:
            visualData.pivot = action.indexOne;
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

        case ActionType::SetPivot:
            visualData.pivot = action.indexTwo;
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

const size_t SortEngine::getArraySize() const {
    return arraySize;
}

const size_t SortEngine::getActionsSize() const {
    return actions.size();
}

const bool SortEngine::isActionsEmpty() const {
    return actions.empty();
}

const size_t SortEngine::getCurrentActionIndex() const {
    return currentActionIndex;
}

void SortEngine::setArraySize(const size_t newArraySize) {
    arraySize = newArraySize;
}