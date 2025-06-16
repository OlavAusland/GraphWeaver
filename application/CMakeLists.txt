include("${CMAKE_CURRENT_SOURCE_DIR}/GraphWeaverAPI.cmake")

add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(python_api)

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
    core
    graphics
)

