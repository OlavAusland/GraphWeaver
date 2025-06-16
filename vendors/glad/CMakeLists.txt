add_library(glad STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
)

target_include_directories(glad PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


#target_sources(${CMAKE_PROJECT_NAME} PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
#)
#
#target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/include
#)
