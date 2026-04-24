cmake_minimum_required(VERSION 3.16)
project(ds_and_strpo LANGUAGES CXX)

option(DS_ENABLE_TRACE "Enable constructor/destructor tracing" OFF)
option(DS_USE_PREBUILT_CODEC "Use prebuilt external codec through find_library" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(ds_core STATIC
    src/rect.cpp
    src/barrel.cpp
    src/matrix.cpp
    src/my_string.cpp
    src/text_wrapper.cpp
    src/base_file.cpp
    src/base32_codec.cpp
    src/base32_file.cpp
    src/rle_codec.cpp
    src/rle_file.cpp
    src/composed_files.cpp
    src/worker_db.cpp
    src/notification.cpp
    src/bool_array.cpp
)

target_include_directories(ds_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(ds_core PUBLIC cxx_std_17)

if(DS_ENABLE_TRACE)
    target_compile_definitions(ds_core PRIVATE DS_TRACE_LIFETIME)
endif()

if(DS_USE_PREBUILT_CODEC)
    set(PREBUILT_CODEC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/simple_codec")
    find_library(SIMPLE_CODEC_LIBRARY
        NAMES simple_codec
        PATHS "${PREBUILT_CODEC_ROOT}" "${PREBUILT_CODEC_ROOT}/lib"
        NO_DEFAULT_PATH
    )
    if(NOT SIMPLE_CODEC_LIBRARY)
        message(FATAL_ERROR "Prebuilt simple_codec library was not found in ${PREBUILT_CODEC_ROOT}. Build external/simple_codec separately and copy the static library there.")
    endif()
    add_library(simple_codec_external STATIC IMPORTED)
    set_target_properties(simple_codec_external PROPERTIES IMPORTED_LOCATION "${SIMPLE_CODEC_LIBRARY}")
    add_library(ds_external_codec STATIC src/external_codec_adapter.cpp)
    target_include_directories(ds_external_codec
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/simple_codec/include
    )
    target_link_libraries(ds_external_codec PUBLIC simple_codec_external)
endif()

add_executable(lab1_demo apps/lab1_demo.cpp)
target_link_libraries(lab1_demo PRIVATE ds_core)
add_executable(lab2_demo apps/lab2_demo.cpp)
target_link_libraries(lab2_demo PRIVATE ds_core)
add_executable(lab3_demo apps/lab3_demo.cpp)
target_link_libraries(lab3_demo PRIVATE ds_core)

foreach(test_name
    test_rect_basic_methods
    test_rect_properties
    test_rect_operations
    test_bounding_rect
    test_barrel
    test_text_wrapper
    test_file_roundtrip
    test_large_file_roundtrip
    test_base_file_move
    test_my_string_lab3
    test_matrix_lab3
    test_worker_db
    test_notification_queues
    test_bool_array)
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} PRIVATE ds_core)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
