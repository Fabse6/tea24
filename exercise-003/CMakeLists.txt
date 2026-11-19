configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
    @ONLY
)

add_executable(exercise-003
    main.cpp
)

target_link_libraries(exercise-003
    PRIVATE
        version
        fmt::fmt
)

add_executable(version_cli
    version_cli.cpp
)

target_link_libraries(version_cli
    PRIVATE
        version
        fmt::fmt
)

add_executable(version_shared_cli
    version_cli.cpp
)

target_link_libraries(version_shared_cli
    PRIVATE
        version_shared
        fmt::fmt
)

add_executable(c_consumer
    c_consumer.c
)

target_link_libraries(c_consumer
    PRIVATE
        version
)

set_target_properties(c_consumer PROPERTIES LINKER_LANGUAGE CXX)

add_executable(version_tests
    version_tests.cpp
)

target_link_libraries(version_tests
    PRIVATE
        version
)

if(BUILD_TESTS)
    add_test(NAME version_tests COMMAND version_tests)
endif()