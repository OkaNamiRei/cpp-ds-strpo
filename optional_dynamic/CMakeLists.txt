cmake_minimum_required(VERSION 3.16)
project(optional_dynamic_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(implicit_cat SHARED
    implicit/implicit_cat.cpp
)
target_include_directories(implicit_cat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/implicit)

add_library(explicit_cat SHARED
    explicit/explicit_cat.cpp
)
target_include_directories(explicit_cat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/explicit)

add_executable(dynamic_loader
    loader/main.cpp
)

target_include_directories(dynamic_loader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/implicit)
target_link_libraries(dynamic_loader PRIVATE implicit_cat)

if(WIN32)
    target_compile_definitions(dynamic_loader PRIVATE DYNAMIC_LOADER_WINDOWS)
else()
    target_link_libraries(dynamic_loader PRIVATE dl)
endif()