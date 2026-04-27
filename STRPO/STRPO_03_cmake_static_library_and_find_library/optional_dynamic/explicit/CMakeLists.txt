cmake_minimum_required(VERSION 3.16)
project(explicit_cat_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(explicit_cat SHARED explicit_cat.cpp)
