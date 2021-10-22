cmake_minimum_required(VERSION 3.16)

add_library(Boost INTERFACE)

target_include_directories(Boost INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")