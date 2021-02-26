cmake_minimum_required(VERSION 3.10)
project(sfmlRaycaster)

set(CMAKE_CXX_STANDARD 17)
add_compile_options ( -DSFML_STATIC )
include_directories(src)

if(WIN32 OR WIN64)
	set(SFML_STATIC_LIBRARIES TRUE)
	set(BUILD_SHARED_LIBS FALSE)
	execute_process(COMMAND git submodule update --init --recursive)
	add_subdirectory(lib/SFML)
endif()

add_subdirectory(src)
