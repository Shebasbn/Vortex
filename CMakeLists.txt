cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Dist>:Dist>")

add_subdirectory("Sandbox")
add_subdirectory("Vortex/vendor/spdlog")

project("Vortex")
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES CMAKE_CONFIGURE_DEPENDS "Vortex/src/*.cpp" "Vortex/src/*.h")

add_library("Vortex" STATIC "${SOURCES}")


target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ${CMAKE_PROJECT_NAME}_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Vortex/") 
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ${CMAKE_PROJECT_NAME}_PATH="./${CMAKE_PROJECT_NAME}/") 


target_include_directories("Vortex" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include/")
target_link_libraries("Vortex" "spdlog")





