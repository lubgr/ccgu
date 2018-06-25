
add_library(cggu
    INTERFACE)

target_compile_features(cggu
    INTERFACE
    cxx_std_14)

include(GNUInstallDirs)

target_include_directories(cggu
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_include_directories(cggu
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

add_library(cggu::cggu ALIAS cggu)

install(DIRECTORY cggu
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT development)
