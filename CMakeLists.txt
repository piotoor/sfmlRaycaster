cmake_minimum_required(VERSION 3.10)
project(sfmlRaycaster)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(src)
if(WIN32 OR WIN64)
  add_custom_target(
      sfmlRepo
      command cmd /c sfmlRepo.bat
  )
  add_dependencies(${BINARY}_run sfmlRepo)
  add_subdirectory(lib/SFML)
endif()
