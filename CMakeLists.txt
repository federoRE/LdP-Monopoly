# Author JFK

# TODO modificare il file per adattarlo al progetto

cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME LdP-Monopoly)
project(${PROJECT_NAME} VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

set(
    SRC_FILES 
    src/CircularArray.hpp
    src/Player.cpp 
    src/Property.cpp
    src/Logger.cpp
    src/Game.cpp
    )

set(
    HEADER_FILES 
    include/CircularArray.h 
    include/Player.h 
    include/Property.h
    include/Logger.h
    include/Game.h
    )

SET(GCC_COVERAGE_COMPILE_FLAGS "-O2")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories(include src)

add_library(
    monopoly_lib
    ${SRC_FILES} 
    ${HEADER_FILES}
    )
# MAIN EXECUTABLE
add_executable(
    Monopoly
    src/main.cpp
    )
target_link_libraries(
    Monopoly 
    monopoly_lib
    )

# TESTING EXECUTABLES
add_executable(
    player_array_prop_test
    src/tests/player_array_prop_test.cpp
    )
add_executable(
    player_test
    src/tests/player_test.cpp
    )
add_executable(
    circulararray_test
    src/tests/circulararray_test.cpp
    )

target_link_libraries(player_array_prop_test monopoly_lib)
target_link_libraries(player_test monopoly_lib)
target_link_libraries(circulararray_test monopoly_lib)
enable_testing()


add_test(
    NAME player_array_prop_test
    COMMAND $<TARGET_FILE:player_array_prop_test>
)
add_test(
    NAME player_test
    COMMAND $<TARGET_FILE:player_test>
)
add_test(
    NAME circulararray_test
    COMMAND $<TARGET_FILE:circulararray_test>
)
