project(BLSZ VERSION 1.0.0 LANGUAGES CXX)

add_library(BLSZ INTERFACE)
target_include_directories(BLSZ INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(BLSZ INTERFACE Boost)