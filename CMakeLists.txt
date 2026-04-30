cmake_minimum_required(VERSION 4.3)
project(SortingVisualizer)
set(CMAKE_CXX_STANDARD 17)

set(SFML_DIRECTORY "C:/libraries/SFML/lib/cmake/SFML")

find_package(
    SFML 3 
    COMPONENTS Graphics Window System Main 
    PATHS ${SFML_DIRECTORY}
    NO_DEFAULT_PATH    
    REQUIRED
)

set(SOURCE_FILES 
    src/app.cpp
    src/render.cpp
    src/sort-engine.cpp
)

add_library(lib ${SOURCE_FILES})
target_include_directories(lib PUBLIC includes/)
target_link_libraries(lib PUBLIC SFML::Graphics SFML::Window SFML::System)

add_executable(app src/main.cpp)

target_link_libraries(app PRIVATE lib SFML::Main)