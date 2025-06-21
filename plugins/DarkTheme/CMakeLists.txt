cmake_minimum_required(VERSION 3.19)
project(DarkTheme)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(${CMAKE_PROJECT_NAME} SHARED main.cpp)

include("${CMAKE_SOURCE_DIR}/../../cmake/GraphWeaverConfig.cmake")
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE GraphWeaver::API)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PREFIX "")


