cmake_minimum_required(VERSION "3.26")

project(CS162-Course-Registration-System)

FILE(GLOB SOURCES *.cpp Function/**/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

add_executable(CRS ${SOURCES})
