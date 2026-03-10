cmake_minimum_required(VERSION 3.16)

project(GuessingGameProject
  VERSION 1.0
  DESCRIPTION "Simple number guessing game"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# For IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Werror
)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(guessinggame
    src/main.cpp
    src/game.cpp
)

target_include_directories(guessinggame PRIVATE include)

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
