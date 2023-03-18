cmake_minimum_required(VERSION 3.0.0)
project(SDL2Game VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(SDL2Game main.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(src)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(SDL2Game
  PUBLIC My_library
  PUBLIC ${SDL2_LIBRARIES}
  PUBLIC ${SDL2_IMAGE_LIBRARIES}
)
