cmake_minimum_required(VERSION 3.16)

project(JSONParser
  VERSION 1.0
  DESCRIPTION "Simple CPP tool to parse json files"
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

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(jsoncpp ${SRC_FILES})

target_include_directories(jsoncpp PRIVATE include)

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
