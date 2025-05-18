cmake_minimum_required(VERSION "3.19.2")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory("Vortex")

project("Sandbox")
add_executable("Sandbox" "Sandbox/src/SandboxApp.cpp")
target_include_directories("Sandbox" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Vortex/src/")
target_link_libraries("Sandbox" "Vortex")


