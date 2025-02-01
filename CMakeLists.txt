cmake_minimum_required(VERSION 3.16)
project(decisions VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:DLL>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:DebugDLL>")
endif()


# Force MD/MDd runtime library
if (MSVC)
    # Iterate over all standard MSVC flag variables
    foreach (flag_var
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        # Ensure MT/MTd flags are replaced with MD/MDd correctly
        string(REPLACE "/MT" "/MD" ${flag_var} "${${flag_var}}")
        string(REPLACE "/MTd" "/MDd" ${flag_var} "${${flag_var}}")
    endforeach ()
endif ()

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

# Install rules
install(TARGETS decisions
    EXPORT decisionsTargets            # Export target information
    ARCHIVE DESTINATION lib            # Static library location
    LIBRARY DESTINATION lib            # Shared library location (if SHARED is used)
    RUNTIME DESTINATION bin            # Executable location (for shared libs on Windows)
)

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Export target configuration
install(EXPORT decisionsTargets
    FILE decisionsTargets.cmake
    NAMESPACE decisions::
    DESTINATION lib/cmake/decisions
)

# Install project config
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/decisionsConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/decisionsConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/decisionsConfig.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_BINARY_DIR}/decisionsConfig.cmake"
    "${CMAKE_BINARY_DIR}/decisionsConfigVersion.cmake"
    DESTINATION lib/cmake/decisions
)

# Enable testing
enable_testing()

# Add subdirectory for tests
add_subdirectory(tests)
