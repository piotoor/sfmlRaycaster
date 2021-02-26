set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})
add_executable(${BINARY}_run ${SOURCES})
if(WIN32 OR WIN64)
	include_directories(..\\lib\\SFML\\include)
	target_link_libraries(${BINARY}_run sfml-window sfml-system sfml-graphics)

else()
	target_link_libraries(${BINARY}_run sfml-window sfml-system sfml-graphics pthread X11)
endif()
