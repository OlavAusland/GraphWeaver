target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    Graphics.cpp
    Canvas.cpp
    Shader.cpp
    DrawManager.cpp
    LineObject.cpp
    PlaneObject.cpp
    DrawObject.cpp
    PointObject.cpp
    ShaderManager.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    "${CMAKE_PROJECT_NAME}/application/core/"
)
