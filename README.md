# Sorting Visualizer

A high-performance sorting algorithm visualizer built from scratch using C++ and the Simple and Fast Multimedia Library (SFML). Featuring a custom rendering engine, it includes a timeline scrubber that allows you to control the visualization like a video player.

<!-- Include the GIF here -->

## The Architecture (Overview)

The core, unique feature of this program is its custom timeline scrubber. Most visualizers force the user to watch a sort from start to end. This project changes that, using **delta encoding** to perfectly record changes in the array as it sorts as reversible actions. 

This architecture allows the user to: 
- Pause and resume the animation at any moment
- Step forward or backwards frame-by-frame to properly digest each step in an algorithm
- Use the timeline slider to seamlessly scrub backward and forward through time

## Usage

Using this program is as simple as clicking on the screen with your mouse! Interact with the control deck to randomize the array, change the array size, adjust the sorting delay, cycle algorithms, and scrub through the animation!

Beyond the GUI, you can also control certain aspects with shortcuts:
- **Up/Down Arrows**: Cycle algorithms
- **Left/Right Arrows**: Step forward or backwards in time, respectively
- **Space Bar**: Pause or play animation
- **R**: Restart animation
- **Scroll Wheel**: If the mouse is near the sorting algorithm's name, scroll to cycle algorithms

## Build Instructions

If you want to build the program yourself, you will need these prerequisites:

1. CMake v3.16 or higher
2. C++20 Compiler (e.g., GCC, MSVC, Clang)
3. SFML v3.x or higher

### Compiling on macOS / Linux

Unix-based systems can natively resolve SFML if installed via a package manager.

1. Install SFML v3.x using your package manager:

    ```
    macOS: brew install sfml
    ```
    ```
    Ubuntu/Debian: sudo apt-get install libsfml-dev
    ```

2. Clone the repository:

    ```bash
    git clone https://github.com/YOUR_USERNAME/SortingVisualizer.git
    cd SortingVisualizer
    ```

3. Generate the build files. You do not need to provide a Unix-based system with the directory to your SFML.

    ```bash
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ```

4. Run the application:

    ```bash
    ./build/app
    ```

### Compiling on Windows

1. Clone the repository:
    ```bash
    git clone https://github.com/Proderp/SortingVisualizer.git
    cd SortingVisualizer
    ```

2. Generate the build files. For Windows, must provide CMake with the path to your SFML installation's CMake directory using the -DSFML_DIR flag:

    ```bash
    cmake -B build -DSFML_DIR="C:/path/to/your/SFML/lib/cmake/SFML"
    ```

3. Compile the executable:

    ```bash
    cmake --build build --config Release
    ```

You should now have an executable, but it still needs to be linked. If you are compiling on Windows using dynamic linking, app.exe requires the SFML .dll files to run. If you attempt to launch the executable directly and receive a "Missing DLL" error, choose one of the following solutions:

>**Option A**: Add the bin directory of your SFML installation (e.g., C:/SFML/bin) to your Windows System PATH environment variable. This allows Windows to locate the DLLs automatically for all future projects.

>**Option B (Manual)**: Copy `sfml-graphics-3.dll`, `sfml-window-3.dll`, and `sfml-system-3.dll` from your SFML bin directory and paste them directly into your build/Release folder right next to app.exe.

Once you have done all of that, you can now run app.exe by just double-clicking it or running: 

```bash
.\build\Release\app.exe
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.