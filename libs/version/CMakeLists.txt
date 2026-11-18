cmake_minimum_required(VERSION 3.10.2)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version_config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/version/version_config.h"
    @ONLY
)

add_library(version STATIC
    src/version.cpp
)

target_include_directories(version
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/include
)
