cmake_minimum_required(VERSION 3.16)
project(strpo3_optional_dynamic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(implicit_cat SHARED implicit/implicit_cat.cpp)
target_compile_definitions(implicit_cat PRIVATE IMPLICIT_CAT_EXPORTS)
target_include_directories(implicit_cat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/implicit)

add_executable(dynamic_loader loader/main.cpp)
target_link_libraries(dynamic_loader PRIVATE implicit_cat)
target_include_directories(dynamic_loader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/implicit)

if(UNIX AND NOT APPLE)
    target_link_libraries(dynamic_loader PRIVATE dl)
endif()

if(WIN32)
    add_custom_command(TARGET dynamic_loader POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:implicit_cat>
                $<TARGET_FILE_DIR:dynamic_loader>)
endif()
