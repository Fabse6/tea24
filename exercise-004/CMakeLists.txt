project(exercise-004 VERSION 1.0.0 LANGUAGES C CXX)

# Teil A: Eine Quelldatei und ein Header
add_executable(exercise-004 main.cpp)

# Teil B: Zwei Quelldateien mit einer Deklaration und einer Definition
add_executable(exercise-004-01
    exercise-004-01/main.c
    exercise-004-01/greet.c
)

# Teil C/D: Statische und dynamische Varianten der eigenen Bibliothek
add_library(greet-static STATIC exercise-004-01/greet.c)
set_target_properties(greet-static PROPERTIES OUTPUT_NAME greet)

add_library(greet-shared SHARED exercise-004-01/greet.c)
set_target_properties(greet-shared PROPERTIES OUTPUT_NAME greet)

target_include_directories(greet-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01)
target_include_directories(greet-shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01)

add_executable(exercise-004-main-static exercise-004-01/main.c)
target_link_libraries(exercise-004-main-static PRIVATE greet-static)

add_executable(exercise-004-main-dynamic exercise-004-01/main.c)
target_link_libraries(exercise-004-main-dynamic PRIVATE greet-shared)

# Teil C: Vollstaendig statisch gelinktes Programm
add_executable(exercise-004-full-static exercise-004-01/main.c)
target_link_libraries(exercise-004-full-static PRIVATE greet-static)
target_link_options(exercise-004-full-static PRIVATE -static)

# Teil A: Alle vier Stufen als reproduzierbares CMake-Ziel
set(STAGE_DIR ${CMAKE_CURRENT_BINARY_DIR}/stages)
add_custom_target(exercise-004-stages
    COMMAND ${CMAKE_COMMAND} -E make_directory ${STAGE_DIR}
    COMMAND ${CMAKE_C_COMPILER} -E ${CMAKE_CURRENT_SOURCE_DIR}/main.c -I${CMAKE_CURRENT_SOURCE_DIR} -o ${STAGE_DIR}/main.i
    COMMAND ${CMAKE_C_COMPILER} -S ${STAGE_DIR}/main.i -o ${STAGE_DIR}/main.s
    COMMAND ${CMAKE_C_COMPILER} -c ${STAGE_DIR}/main.s -o ${STAGE_DIR}/main.o
    COMMAND nm ${STAGE_DIR}/main.o
    COMMAND objdump -dr ${STAGE_DIR}/main.o
    COMMAND ${CMAKE_C_COMPILER} ${STAGE_DIR}/main.o -o ${STAGE_DIR}/main
    COMMAND ${STAGE_DIR}/main
    COMMAND objdump -d ${STAGE_DIR}/main
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Fuehrt die vier Uebersetzungsstufen aus Teil A aus"
)

# Teil B: Objektdateien, Symbole und der absichtlich provozierte Linkfehler
set(PART_B_DIR ${CMAKE_CURRENT_BINARY_DIR}/part-b)
add_custom_target(exercise-004-part-b
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PART_B_DIR}
    COMMAND ${CMAKE_C_COMPILER} -c ${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01/main.c
            -I${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01 -o ${PART_B_DIR}/main.o
    COMMAND ${CMAKE_C_COMPILER} -c ${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01/greet.c
            -I${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01 -o ${PART_B_DIR}/greet.o
    COMMAND nm ${PART_B_DIR}/main.o
    COMMAND nm ${PART_B_DIR}/greet.o
    COMMAND ${CMAKE_C_COMPILER} ${PART_B_DIR}/main.o ${PART_B_DIR}/greet.o
            -o ${PART_B_DIR}/main
    COMMAND ${PART_B_DIR}/main
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Zeigt offene und definierte Symbole sowie undefined-reference"
)

# Teil D: Eigenes statisches Archiv und Shared Library
set(PART_D_DIR ${CMAKE_CURRENT_BINARY_DIR}/part-d)
add_custom_target(exercise-004-part-d
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PART_D_DIR}
    COMMAND ${CMAKE_C_COMPILER} -c ${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01/greet.c
            -I${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01 -fPIC -o ${PART_D_DIR}/greet.o
    COMMAND ar rcs ${PART_D_DIR}/libgreet.a ${PART_D_DIR}/greet.o
    COMMAND ar t ${PART_D_DIR}/libgreet.a
    COMMAND nm -A ${PART_D_DIR}/libgreet.a
    COMMAND ${CMAKE_C_COMPILER} -c ${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01/main.c
            -I${CMAKE_CURRENT_SOURCE_DIR}/exercise-004-01 -o ${PART_D_DIR}/main.o
    COMMAND ${CMAKE_C_COMPILER} ${PART_D_DIR}/main.o -L${PART_D_DIR}
            -lgreet -o ${PART_D_DIR}/main_lib
    COMMAND ${PART_D_DIR}/main_lib
    COMMAND ${CMAKE_C_COMPILER} -fPIC -shared ${PART_D_DIR}/greet.o
            -Wl,-soname,libgreet.so -o ${PART_D_DIR}/libgreet.so
    COMMAND ${CMAKE_C_COMPILER} ${PART_D_DIR}/main.o -L${PART_D_DIR}
            -lgreet -Wl,-rpath=${PART_D_DIR} -o ${PART_D_DIR}/main_so
    COMMAND ldd ${PART_D_DIR}/main_so
    COMMAND ${PART_D_DIR}/main_so
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Baut und prueft ein eigenes .a- und .so-Archiv"
)

