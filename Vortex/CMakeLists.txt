cmake_minimum_required(VERSION "3.19.2")
set(CMAKE_CXX_STANDARD 17)

project("Vortex")
add_library("Vortex" STATIC "src/EntryPoint.cpp" "src/Application.h" "src/Application.cpp")