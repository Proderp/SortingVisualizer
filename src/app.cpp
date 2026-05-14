#include "app.hpp"

App::App() : 
    window(sf::VideoMode({DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}), "Sorting Visualizer"),
    windowSize(static_cast<sf::Vector2f>(window.getSize())),
    ui(window, windowSize, sortingEngine.getArray()),
    renderer(window, ui)
{
    setArraySizeThumb();
    setDelayThumb();
    ui.setSortCycleAlgorithm(algorithm);
}

void App::run() {
    while (window.isOpen()) {
        eventLoop();
        checkClock();
        render();
    }
}

void App::eventLoop() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const sf::Event::Resized* resizeEvent = event->getIf<sf::Event::Resized>()) {
            windowSize = static_cast<sf::Vector2f>(resizeEvent->size);
            ui.updateUI(sortingEngine.getArray());
        }

        if (const sf::Event::MouseButtonPressed* mousePressedEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressedEvent->button == sf::Mouse::Button::Left) {
                handleLeftClick(mousePressedEvent);
            } 
        }

        if (const sf::Event::MouseMoved* mouseMovedEvent = event->getIf<sf::Event::MouseMoved>()) {
            if (draggedSlider != ButtonType::None) {
                const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(mouseMovedEvent->position);
                handleSliderEvent(mousePosition);
            }
        }

        if (const sf::Event::MouseButtonReleased* mouseButtonReleeasedEvent = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseButtonReleeasedEvent->button == sf::Mouse::Button::Left) {
                draggedSlider = ButtonType::None;
            }
        }

        if (const sf::Event::KeyPressed* keyPressedEvent = event->getIf<sf::Event::KeyPressed>()) {
            handleKeyPressedEvent(keyPressedEvent);
        }
    }
}

void App::handleSliderEvent(const sf::Vector2f mousePosition) {
    std::optional<SliderEvent> event = ui.checkSliderClick(mousePosition, draggedSlider, sortingEngine.getActionsSize());

    if (!event.has_value()) {
        return;
    }

    if (event->id == ButtonType::AnimationSlider and sortingEngine.isActionsEmpty()) {
        ui.resetAnimationSlider();
        draggedSlider = ButtonType::None; 
        return;
    }

    draggedSlider = event->id;

    switch (event->id) {
        case ButtonType::AnimationSlider: {
            isSorting = false;
            const Index targetIndex = static_cast<Index>(event->percentage * sortingEngine.getActionsSize());
            sortingEngine.scrubAnimation(targetIndex);
            updatePlayButtonSymbol();
            break;
        }
        case ButtonType::ArraySizeSlider: 
            updateArraySizeThumb(event.value());
            break;
        case ButtonType::DelaySlider: {
            updateDelayThumb(event.value());
            break;
        }
    }
}

void App::updateArraySizeThumb(const SliderEvent& event) {
    const uint16_t potentialSize = static_cast<uint16_t>(MAX_ARRAY_SIZE * event.percentage);
    const uint16_t newArraySize = std::clamp(potentialSize, MIN_ARRAY_SIZE, MAX_ARRAY_SIZE);
    
    if (newArraySize == sortingEngine.getArraySize()) {
        return;
    }
    
    stopSorting();
    sortingEngine.setArraySize(newArraySize);
    
    if (dataType == DataType::Consecutive) {
        sortingEngine.randomizeArrayConsecutively();
    } else {
        sortingEngine.randomizeArray();
    }

    ui.updateUI(sortingEngine.getArray());
}

void App::updateDelayThumb(const SliderEvent& event) {
    const sf::Time newDelay = sf::milliseconds(MAX_LATENCY * event.percentage);
    delay = newDelay;
}

void App::handleLeftClick(const sf::Event::MouseButtonPressed* mousePressedEvent) {
    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(mousePressedEvent->position);
    const ButtonType clickedButton = ui.findClickedButton(mousePosition);

    switch (clickedButton) {
        using enum ButtonType;
        case Play:
            handlePlayButton();
            break;
        case StepBack:
            stepBack();
            break;
        case StepForward:
            stepForward();
            break;
        case Randomize:
            stopSorting();
            sortingEngine.randomizeArray();
            ui.updateUI(sortingEngine.getArray());
            break;
        case Consecutive:
            stopSorting();
            sortingEngine.randomizeArrayConsecutively();
            ui.updateUI(sortingEngine.getArray());
            break;
        case RightArrow:
            cycleAlgorithms(true);
            break;
        case LeftArrow:
            cycleAlgorithms(false);
            break;
        case None:
            break;
    }
    
    handleSliderEvent(mousePosition);
}

void App::handlePlayButton() {
    if (sortingEngine.isActionsEmpty()) {
        stopSorting();
        startSorting();
        isSorting = true;
        ui.setPlayButtonSymbol(pauseSymbol);
    } else if (sortingEngine.getCurrentActionIndex() >= sortingEngine.getActionsSize()) {
        restartAnimation();
        ui.setPlayButtonSymbol(pauseSymbol);
    } else {
        if (isSorting) {
            ui.setPlayButtonSymbol(playSymbol);
        } else {
            ui.setPlayButtonSymbol(pauseSymbol);
        }
        isSorting = !isSorting;
    }
}

void App::handleKeyPressedEvent(const sf::Event::KeyPressed* keyPressedEvent) {
    switch (keyPressedEvent->scancode) {
        using enum sf::Keyboard::Scancode;
        case Left:
            stepBack();
            break;

        case Right:
            stepForward();
            break;
        
        case Space:
            handlePlayButton();
            break;
        
        case R:
            restartAnimation();
            updatePlayButtonSymbol();
            break;    
    }
}

void App::stepButtonUpdate() {
    isSorting = false;
    updateAnimationThumb();
    updatePlayButtonSymbol();
}

void App::stepBack() {
    sortingEngine.runActionBackward();
    stepButtonUpdate();
}

void App::stepForward() {
    sortingEngine.runActionForward();
    stepButtonUpdate();
}

void App::cycleAlgorithms(const bool scrolledRight) {
    if (scrolledRight) {
        getNextAlgorithm();
    } else {
        getPreviousAlgorithm();
    }

    ui.setSortCycleAlgorithm(algorithm);
    handleSwitchedAlgorithm();
    updatePlayButtonSymbol();
}

void App::getNextAlgorithm() {
    int currentIndex = static_cast<int>(algorithm);
    int totalAlgos = static_cast<int>(Algorithm::Count);

    int nextIndex = (currentIndex + 1) % totalAlgos;

    algorithm = static_cast<Algorithm>(nextIndex);
}

void App::getPreviousAlgorithm() {
    int currentIndex = static_cast<int>(algorithm);
    int totalAlgos = static_cast<int>(Algorithm::Count);

    int prevIndex = (currentIndex - 1 + totalAlgos) % totalAlgos;

    algorithm = static_cast<Algorithm>(prevIndex);
}

void App::handleSwitchedAlgorithm() {
    if (sortingEngine.isActionsEmpty()) {
        return; 
    }

    const bool wasPaused = !isSorting;

    stopSorting();
    sortingEngine.copyBaseArray();
    startSorting(); 
    
    isSorting = !wasPaused;
}

void App::restartAnimation() {
    if (!sortingEngine.isActionsEmpty()) {
        sortingEngine.scrubAnimation(0);
        updateAnimationThumb();
        isSorting = true;
    }
}

void App::startSorting() {
    switch (algorithm) {
        using enum Algorithm;
        case Bubble:
            sortingEngine.bubbleSort();
            break;
        case Insertion:
            sortingEngine.insertionSort();
            break;
        case Merge:
            sortingEngine.mergeSortWrapper();
            break;
        case Quick:
            sortingEngine.quickSortWrapper();
            break;
    }
}

void App::stopSorting() {
    isSorting = false;
    sortingEngine.resetActions();
    sortingEngine.resetVisualData();
    ui.resetAnimationSlider();
}

void App::updatePlayButtonSymbol() {
    if (sortingEngine.isActionsEmpty()) {
        ui.setPlayButtonSymbol(playSymbol);
    } else if (sortingEngine.getCurrentActionIndex() >= sortingEngine.getActionsSize()) {
        ui.setPlayButtonSymbol(restartSymbol);
    } else if (isSorting) {
        ui.setPlayButtonSymbol(pauseSymbol);
    } else {
        ui.setPlayButtonSymbol(playSymbol);
    }
}

void App::checkClock() {
    if (clock.getElapsedTime() >= delay and isSorting) {
        clock.restart();

        if (!sortingEngine.runActionForward()) {
            isSorting = false;
            updateAnimationThumb();
            updatePlayButtonSymbol();
            return;
        }

        updateAnimationThumb();
    }
}

void App::updateAnimationThumb() {
    if (!sortingEngine.isActionsEmpty()) {
        float percentage = static_cast<float>(sortingEngine.getCurrentActionIndex()) / sortingEngine.getActionsSize();
        
        ui.setAnimationPercentage(percentage);
        ui.updateAnimationSlider();
    }
}

void App::setArraySizeThumb() {
    float percentage = static_cast<float>(sortingEngine.getArraySize()) / MAX_ARRAY_SIZE;
    ui.setArraySizePercentage(percentage);
    ui.updateSliderLayout();
}

void App::setDelayThumb() {
    float percentage = delay.asMilliseconds() / MAX_LATENCY;
    ui.setDelayPercentage(percentage);
    ui.updateSliderLayout();
}

void App::render() {
    window.clear(sf::Color(25, 25, 28));

    renderer.drawArray(sortingEngine.getArray(), ui.getArrayDimensions(), sortingEngine.getVisualData());
    renderer.drawButtonLayout(ui.getButtonLayout());
    //renderer.drawSliderLayout(ui.getSliderLayout());
    renderer.drawAnimationSlider(ui.getAnimationSlider());
    renderer.drawSortCycler(ui.getSortCycler());

    window.display();
}