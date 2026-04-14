cmake_minimum_required(VERSION 3.16)
project(strpo4_debug_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_LINK_ERROR_DEMO "Build intentionally broken link error target" OFF)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)

add_executable(segfault_demo segfault.cpp)
add_executable(leak_demo leak.cpp)
add_executable(ub_demo ub.cpp)

if(MSVC)
    target_compile_options(segfault_demo PRIVATE /W4)
    target_compile_options(leak_demo PRIVATE /W4)
    target_compile_options(ub_demo PRIVATE /W4)
else()
    target_compile_options(segfault_demo PRIVATE -Wall -Wextra -O0 -g)
    target_compile_options(leak_demo PRIVATE -Wall -Wextra -O0 -g -fsanitize=address)
    target_link_options(leak_demo PRIVATE -fsanitize=address)
    target_compile_options(ub_demo PRIVATE -Wall -Wextra -O0 -g)
endif()

if(BUILD_LINK_ERROR_DEMO)
    add_executable(link_error_demo link_error_main.cpp)
endif()

if(CLANG_TIDY_EXE)
    add_custom_target(tidy_segfault
        COMMAND ${CLANG_TIDY_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/segfault.cpp -- -std=c++17
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )

    add_custom_target(tidy_leak
        COMMAND ${CLANG_TIDY_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/leak.cpp -- -std=c++17
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )

    add_custom_target(tidy_ub
        COMMAND ${CLANG_TIDY_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ub.cpp -- -std=c++17
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
endif()