if(${BACKEND_TYPE} STREQUAL "OPENGL")
    add_subdirectory(OpenGL_Implementation)
    
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL_Implementation/
    )

    message("BUILDING_OPENGL")
elseif(${BACKEND_TYPE} STREQUAL "SDL")
    add_subdirectory(SDL_Implementation)

    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/SDL_Implementation/
    )
else()
    message("NOT A VALID BACKEND")
endif()

