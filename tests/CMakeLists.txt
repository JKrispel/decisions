# Include FetchContent module
include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(test_decisions "test_decision_tree.cpp")

# Link Google Test and your decisions library
target_link_libraries(test_decisions PRIVATE gtest gtest_main decisions)

# Include the project's include directory for the tests
target_include_directories(test_decisions PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
