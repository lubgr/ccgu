
add_executable(duplicate
    duplicate.cpp)

target_link_libraries(duplicate
    PRIVATE
    cggu Boost::unit_test_framework)

add_test(NAME cggu.tests COMMAND tests)

