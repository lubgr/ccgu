
add_executable(duplicate
    duplicate.cpp)

target_compile_options(duplicate
    PRIVATE
    $<$<CONFIG:Release>:-march=native -mtune=native>)

target_link_libraries(duplicate
    PRIVATE
    cggu)
