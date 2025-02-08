cmake_minimum_required(VERSION 3.16)
project(decisions VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add library target
add_library(decisions STATIC 
    src/action_manager/action.cpp
    src/action_manager/action_manager.cpp
    src/decision_tree/decision.cpp
)

# Include directories
target_include_directories(decisions PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # During build
    $<INSTALL_INTERFACE:include>                  # During install
)

# Set library versioning
set_target_properties(decisions PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1)

# Install rules for the library
install(TARGETS decisions
    EXPORT decisionsTargets            # Export target information
    ARCHIVE DESTINATION lib            # Static library location
)

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Export target configuration for downstream projects
install(EXPORT decisionsTargets
    FILE decisionsTargets.cmake
    NAMESPACE decisions::
    DESTINATION lib/cmake/decisions
)

# Include helper module for generating package configuration files
include(CMakePackageConfigHelpers)

# Write the version file
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/decisionsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Configure the package configuration file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/decisionsConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/decisionsConfig.cmake"
    @ONLY
)

# Install the package configuration files
install(FILES
    "${CMAKE_BINARY_DIR}/decisionsConfig.cmake"
    "${CMAKE_BINARY_DIR}/decisionsConfigVersion.cmake"
    DESTINATION lib/cmake/decisions
)
