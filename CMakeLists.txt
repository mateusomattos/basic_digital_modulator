cmake_minimum_required(VERSION 3.0)
project(Simulator C)

set(BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(TEST_OUTPUT_DIR ${BINARY_DIR}/test_executables)
file(MAKE_DIRECTORY ${BINARY_DIR})
file(MAKE_DIRECTORY ${TEST_OUTPUT_DIR})
file(MAKE_DIRECTORY ${BINARY_DIR}/data)

file(GLOB_RECURSE sources src/*.c)
add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE m)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

include_directories(unity/src)
add_library(Unity STATIC unity/src/unity.c)

file(GLOB_RECURSE TEST_SOURCES test/*.c)

foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME}
        ${TEST_FILE}
        src/boxmuller.c
        src/channel.c
        src/cli.c
        src/config.c
        src/modulation.c
        src/output.c
        src/utils.c
    )

    target_link_libraries(${TEST_NAME} PRIVATE Unity)
    target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${TEST_NAME} PRIVATE m)
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
