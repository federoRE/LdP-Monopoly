# Author JFK

# TODO modificare il file per adattarlo al progetto

cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME LdP-Monopoly)
project(${PROJECT_NAME} VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES src/Book.cpp src/Date.cpp src/BookShelf.cpp)
set(HEADER_FILES include/Book.h include/Date.h include/BookShelf.h)
SET(GCC_COVERAGE_COMPILE_FLAGS "-O2")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories(include src)

add_library(
    ${PROJECT_NAME}
    ${SRC_FILES} 
    ${HEADER_FILES}
    )
add_executable(
    Books 
    src/main.cpp
    )
target_link_libraries(
    Books 
    ${PROJECT_NAME}
    )

# TESTING
add_executable(
    book_test
    src/testing/book_test.cpp
    )
add_executable(
    library_test
    src/testing/library_prof_test.cpp
    )
target_link_libraries(book_test ${PROJECT_NAME})
target_link_libraries(library_test ${PROJECT_NAME})
enable_testing()

add_test(
    NAME book_test
    COMMAND $<TARGET_FILE:book_test>
)
add_test(
    NAME library_test
    COMMAND $<TARGET_FILE:library_test>
)

