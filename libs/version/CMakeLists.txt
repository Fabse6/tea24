configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version_config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version_config.h"
    @ONLY
)

set(VERSION_SOURCES
    src/version.cpp
    src/version_c_api.cpp
)

add_library(version STATIC ${VERSION_SOURCES})
add_library(version_shared SHARED ${VERSION_SOURCES})

target_include_directories(version
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
)

target_include_directories(version_shared
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
)