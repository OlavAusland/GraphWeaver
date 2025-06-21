set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(GraphWeaverAPI STATIC 
    core/EventManager.cpp 
    core/EventManager.hpp
    core/Hierarchy.hpp
    core/Entity.hpp
    core/Scripting/Script.cpp

    graphics/Graphics.hpp
)

add_library(GraphWeaver::API ALIAS GraphWeaverAPI)


target_include_directories(GraphWeaverAPI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics
)
