cmake_minimum_required(VERSION 3.16)
project(strpo4_debug_examples LANGUAGES CXX)

option(STRPO4_ENABLE_ASAN "Enable AddressSanitizer where supported" OFF)
option(STRPO4_BUILD_LINK_ERROR_DEMO "Build target that intentionally fails at link stage" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(configure_warning_flags target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic)
    endif()
endfunction()

add_executable(segfault_demo segfault.cpp)
configure_warning_flags(segfault_demo)

add_executable(leak_demo leak.cpp)
configure_warning_flags(leak_demo)

add_executable(ub_demo ub.cpp)
configure_warning_flags(ub_demo)

if(STRPO4_BUILD_LINK_ERROR_DEMO)
    add_executable(link_error_demo link_error_main.cpp)
    configure_warning_flags(link_error_demo)
    # declared_but_not_defined объявлена в заголовке, но не определена намеренно.
    # Эта цель должна падать на этапе линковки.
endif()

if(STRPO4_ENABLE_ASAN)
    if(MSVC)
        foreach(target segfault_demo leak_demo ub_demo)
            target_compile_options(${target} PRIVATE /fsanitize=address)
            target_link_options(${target} PRIVATE /fsanitize=address)
        endforeach()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        foreach(target segfault_demo leak_demo ub_demo)
            target_compile_options(${target} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
            target_link_options(${target} PRIVATE -fsanitize=address)
        endforeach()
    endif()
endif()
