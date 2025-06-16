cmake_minimum_required(VERSION 3.19)
project(GraphWeaver)

#set environment variables
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_FLAGS "--enable-features=UseOzonePlatform --ozone-platform=wayland")
set(BACKEND_TYPE "OPENGL") # [OPENGL, SDL?]
set(CMAKE_BUILD_TYPE Debug)
# create target

if(${BACKEND_TYPE} STREQUAL "OPENGL")
    add_executable(${CMAKE_PROJECT_NAME} main.cpp)
endif()
# find packages
find_package(OpenGL REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# add include directories
include_directories(${Python3_INCLUDE_DIRS})

# add subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendors)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/application)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/plugins)

# link 
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    ImGui::ImGui
    glfw
    glad
    OpenGL::GL
    #SDL3::SDL3
    ${Python3_LIBRARIES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/vendors/glad/include"
)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -rdynamic)
