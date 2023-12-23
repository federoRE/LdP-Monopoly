# Author JFK

# TODO modificare il file per adattarlo al progetto

cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME LdP-Monopoly)
project(${PROJECT_NAME} VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)

set(
    SRC_FILES 
    src/CircularArray.cpp 
    src/Player.cpp 
    src/Property.cpp
    src/Logger.cpp
    )

set(
    HEADER_FILES 
    include/CircularArray.h 
    include/Player.h 
    include/Property.h
    include/Logger.h
    )

SET(GCC_COVERAGE_COMPILE_FLAGS "-O2")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories(include src)

add_library(
    ${PROJECT_NAME}
    ${SRC_FILES} 
    ${HEADER_FILES}
    )
# MAIN EXECUTABLE
add_executable(
    ${PROJECT_NAME} 
    src/main.cpp
    )
target_link_libraries(
    ${PROJECT_NAME}  
    ${PROJECT_NAME}
    )

# TESTING EXECUTABLES
add_executable(
    player_test
    src/tests/book_test.cpp
    )
add_executable(
    property_test
    src/tests/property_test.cpp
    )
add_executable(
    CircularArray_test
    src/tests/CircularArray_test.cpp
    )
target_link_libraries(player_test ${PROJECT_NAME})
target_link_libraries(property_test ${PROJECT_NAME})
target_link_libraries(CircularArray_test ${PROJECT_NAME})
enable_testing()

add_test(
    NAME player_test
    COMMAND $<TARGET_FILE:player_test>
)
add_test(
    NAME property_test
    COMMAND $<TARGET_FILE:property_test>
)
add_test(
    NAME CircularArray_test
    COMMAND $<TARGET_FILE:CircularArray_test>
)

