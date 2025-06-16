#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm)

add_library(ImGui STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
)

add_library(ImGuiAPI INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.h
)
add_library(ImGui::API ALIAS ImGuiAPI)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/glm
)

target_include_directories(ImGuiAPI
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
add_library(ImGui::ImGui ALIAS ImGui)

# set up imgui
#target_sources(${CMAKE_PROJECT_NAME} PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
#)

# check what backend we want to use
# will be able to at least support opengl and sdl
if(${BACKEND_TYPE} STREQUAL "OPENGL")
    message("Using GLFW with OpenGL")
    target_sources(ImGui PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h

        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
    )
else()
    message("Using SDL3 with OpenGL")
    target_sources(ImGui PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlrenderer3.h

        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlrenderer3.cpp

    )
endif()

target_include_directories(ImGui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)
