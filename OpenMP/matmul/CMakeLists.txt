cmake_minimum_required(VERSION 3.10.2)
project(MatMul)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Main executable
include_directories(include)
add_executable(MatMul src/main.cpp)
target_link_libraries(MatMul boost_program_options)

# Google Test unit tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
add_executable(unit_tests src/unit_tests.cpp)
target_link_libraries(unit_tests ${GTEST_LIBRARIES} pthread)

add_test(
    NAME unit_tests
    COMMAND unit_tests
)
