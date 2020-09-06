project("sfmlRaycaster")
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

include_directories(../include)

add_executable(sfmlRaycaster main.cpp
                             raycaster.cpp
                             player.cpp
                             gameMap.cpp)
find_library(SFML_GRAPHICS_LIB sfml-graphics)
find_library(SFML_WINDOW_LIB sfml-window)
find_library(SFML_SYSTEM_LIB sfml-system)

target_link_libraries(sfmlRaycaster PRIVATE "${SFML_GRAPHICS_LIB}")
target_link_libraries(sfmlRaycaster PRIVATE "${SFML_WINDOW_LIB}")
target_link_libraries(sfmlRaycaster PRIVATE "${SFML_SYSTEM_LIB}")
