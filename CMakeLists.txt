project(sf)

cmake_minimum_required(VERSION 2.8)

include_directories(include)

aux_source_directory(src SF_SRC)
add_library(sf ${SF_SRC})

add_subdirectory(tests)
