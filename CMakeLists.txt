project("cmakeTest")
cmake_minimum_required(VERSION 3.16)

add_executable(cmakeTest main.cpp)
find_library(SFML_GRAPHICS_LIB sfml-graphics)
find_library(SFML_WINDOW_LIB sfml-window)
find_library(SFML_SYSTEM_LIB sfml-system)

target_link_libraries(cmakeTest PRIVATE "${SFML_GRAPHICS_LIB}")
target_link_libraries(cmakeTest PRIVATE "${SFML_WINDOW_LIB}")
target_link_libraries(cmakeTest PRIVATE "${SFML_SYSTEM_LIB}")
