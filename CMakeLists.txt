cmake_minimum_required(VERSION 3.0)

project(mh-z19b)


add_library(mh-z19b STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/mh-z19b.c)

target_include_directories(mh-z19b PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
