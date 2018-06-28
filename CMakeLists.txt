
cmake_minimum_required(VERSION 3.8)
project(ccgu VERSION 0.0.0 DESCRIPTION "Cohesionless collection of generic utility functions" LANGUAGES CXX)

option(BUILD_TESTING "Compile unit tests" ON)
option(BUILD_BENCHMARKS "Compile benchmark problems" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(${BUILD_TESTING})
    enable_testing()
    add_subdirectory(lib/catch2)
    add_subdirectory(tests)
endif()

if(${BUILD_BENCHMARKS})
    add_subdirectory(benchmarks)
endif()

add_subdirectory(include)
