set(CORE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${CMAKE_PROJECT_NAME} 
    PUBLIC
    Plugin.cpp
    PluginManager.cpp
    EventManager.cpp
    Hierarchy.cpp
    Entity.cpp
    Inspector.cpp
    Camera.cpp
    Console.cpp
    Scripting/Script.cpp
    Scripting/PyScript.cpp
)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Scripting
)
