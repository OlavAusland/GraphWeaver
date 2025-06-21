project(python_api)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_library(graph_weaver MODULE PythonAPI.cpp)

set_target_properties(graph_weaver PROPERTIES
    PREFIX ""
    SUFFIX ".so"
)

target_include_directories(graph_weaver PRIVATE
    ${Python3_INCLUDE_DIRS}
    "${CMAKE_SOURCE_DIR}/vendors/glm"
    "${CMAKE_SOURCE_DIR}/application/core/Scripting"
    "${CMAKE_SOURCE_DIR}/application/graphics/OpenGL_Implementation"
)
target_link_libraries(graph_weaver PRIVATE ${Python3_LIBRARIES} GraphWeaverAPI glad)
