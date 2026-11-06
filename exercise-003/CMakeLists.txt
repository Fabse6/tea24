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