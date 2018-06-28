
add_executable(test-duplicate
    duplicate.cpp)

target_link_libraries(test-duplicate
    PRIVATE
    cggu Catch2::Catch2)

add_test(NAME cggu.tests COMMAND test-duplicate)
