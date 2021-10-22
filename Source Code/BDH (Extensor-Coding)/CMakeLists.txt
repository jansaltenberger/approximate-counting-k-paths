project(BDH VERSION 1.0.0 LANGUAGES CXX)

add_library(BDH INTERFACE)

target_include_directories(BDH INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")