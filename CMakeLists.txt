
cmake_minimum_required(VERSION 3.8)
project(ccgu VERSION 0.0.0 DESCRIPTION "Cohesionless collection of generic utility functions" LANGUAGES CXX)

option(BUILD_TESTING "Compile unit tests" ON)
option(BUILD_BENCHMARKS "Compile benchmark problems" ON)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.65 REQUIRED OPTIONAL_COMPONENTS unit_test_framework)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(${BUILD_TESTING})
    enable_testing()
    add_subdirectory(tests)
endif()

if(${BUILD_BENCHMARKS})
    add_subdirectory(benchmarks)
endif()

add_subdirectory(include)
