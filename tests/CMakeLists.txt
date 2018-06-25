
add_executable(duplicate
    duplicate.cpp)

target_link_libraries(tests
    PRIVATE
    cggu Boost::unit_test_framework)

add_test(NAME cggu.tests COMMAND tests)

