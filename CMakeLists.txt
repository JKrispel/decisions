cmake_minimum_required(VERSION 3.15)
project(decisions VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add library target
add_library(decisions SHARED
    src/action_manager/action.cpp
    src/action_manager/action_manager.cpp
    src/decision_tree/decision.cpp
    src/decision_tree/final_decision.cpp
   )

# Include directories
target_include_directories(decisions PUBLIC include)

# Enable testing
enable_testing()
add_subdirectory(tests)
