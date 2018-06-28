
add_executable(duplicate
    duplicate.cpp)

target_compile_options(duplicate
    PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
    $<$<CONFIG:Release>:-march=native -mtune=native -Wall -pedantic -Wsign-conversion -Wconversion>>)

target_link_libraries(duplicate
    PRIVATE
    cggu)
