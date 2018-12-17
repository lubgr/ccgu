
add_executable(runtests
    main.cpp
    duplicate.cpp
    transformopt.cpp)

 target_compile_options(runtests
    PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -pedantic -Wsign-conversion -Wconversion>)

target_link_libraries(runtests
    PRIVATE
    cggu Catch2::Catch2)

add_test(NAME cggu.tests COMMAND runtests)
