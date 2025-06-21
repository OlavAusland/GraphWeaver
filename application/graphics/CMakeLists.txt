if(${BACKEND_TYPE} STREQUAL "OPENGL")
    add_subdirectory(OpenGL_Implementation)
    
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGL_Implementation/
    )

    message("BUILDING_OPENGL")
else()
    message("NOT A VALID BACKEND")
endif()

