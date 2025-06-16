# Only build GLM as a header-only interface library
add_library(glm-header-only INTERFACE)
add_library(glm::glm-header-only ALIAS glm-header-only)

# Correct include path (this is key!)
target_include_directories(glm-header-only INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

# Make glm::glm target link glm-header-only
add_library(glm INTERFACE)
add_library(glm::glm ALIAS glm)
target_link_libraries(glm INTERFACE glm-header-only)

