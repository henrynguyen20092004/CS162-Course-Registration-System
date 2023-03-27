cmake_minimum_required(VERSION "3.26")

project(CS162-Course-Registration-System)

FILE(GLOB_RECURSE SOURCES FOLLOW_SYMLINKS CONFIGURE_DEPENDS main.cpp Function/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_executable(CRS ${SOURCES})
