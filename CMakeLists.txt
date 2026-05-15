cmake_minimum_required(VERSION 3.16)
project(SortingVisualizer)
set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3 COMPONENTS Graphics Window System Main REQUIRED)

set(SOURCE_FILES 
    src/app.cpp
    src/render.cpp
    src/sort-engine.cpp
    src/ui.cpp
    src/ui-elements.cpp
)

add_library(lib ${SOURCE_FILES})
target_include_directories(lib PUBLIC includes/)
target_link_libraries(lib PUBLIC SFML::Graphics SFML::Window SFML::System)

add_executable(app WIN32 src/main.cpp)

target_link_libraries(app PRIVATE lib SFML::Main)

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/fonts"
    "$<TARGET_FILE_DIR:app>/fonts"
)