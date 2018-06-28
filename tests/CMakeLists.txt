
add_executable(test-duplicate
    duplicate.cpp)

target_compile_options(test-duplicate
    PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -pedantic -Wsign-conversion -Wconversion>)

target_link_libraries(test-duplicate
    PRIVATE
    cggu Catch2::Catch2)

add_test(NAME cggu.tests COMMAND test-duplicate)
