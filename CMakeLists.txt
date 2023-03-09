cmake_minimum_required(VERSION "3.26")

project(CS162-Course-Registration-System)

FILE(GLOB SOURCES *.cpp Function/**/*.cpp)

add_executable(CRS ${SOURCES})
