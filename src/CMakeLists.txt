project("sfmlRaycaster")
cmake_minimum_required(VERSION 3.16)

include_directories(../include)

add_executable(sfmlRaycaster main.cpp
                             gameMap.cpp)
find_library(SFML_GRAPHICS_LIB sfml-graphics)
find_library(SFML_WINDOW_LIB sfml-window)
find_library(SFML_SYSTEM_LIB sfml-system)

target_link_libraries(sfmlRaycaster PRIVATE "${SFML_GRAPHICS_LIB}")
target_link_libraries(sfmlRaycaster PRIVATE "${SFML_WINDOW_LIB}")
target_link_libraries(sfmlRaycaster PRIVATE "${SFML_SYSTEM_LIB}")
