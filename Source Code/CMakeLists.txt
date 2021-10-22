cmake_minimum_required(VERSION 3.16)

project(approximate_k_paths VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory("Boost")

add_subdirectory("BDH (Extensor-Coding)")
add_subdirectory("BLSZ (Divide-And-Color)")
add_subdirectory("Experiments")