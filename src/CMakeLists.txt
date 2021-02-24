set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})
add_executable(${BINARY}_run ${SOURCES})


if(WIN32 OR WIN64)
  find_library(SFML_GRAPHICS_LIB sfml-graphics HINTS "../lib/SFML")
  find_library(SFML_WINDOW_LIB sfml-window HINTS "../lib/SFML")
  find_library(SFML_SYSTEM_LIB sfml-system HINTS "../lib/SFML")
  target_link_libraries(${BINARY}_run sfml-window sfml-system sfml-graphics)
else()
  target_link_libraries(${BINARY}_run sfml-window sfml-system sfml-graphics pthread X11)
endif()

#target_link_libraries(${BINARY}_run PRIVATE "${SFML_GRAPHICS_LIB}")
#target_link_libraries(${BINARY}_run PRIVATE "${SFML_WINDOW_LIB}")
#target_link_libraries(${BINARY}_run PRIVATE "${SFML_SYSTEM_LIB}")
