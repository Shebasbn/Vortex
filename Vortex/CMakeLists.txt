cmake_minimum_required(VERSION "3.19.2")
project("Vortex")
set(CMAKE_CXX_STANDARD 17)

# Support custom config types (for multi-config generators)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)


# Default for single-config generators
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Add vendor dependencies
add_subdirectory(Vortex/vendor/spdlog)


file(GLOB_RECURSE SOURCES CMAKE_CONFIGURE_DEPENDS "Vortex/src/*.cpp" "Vortex/src/*.h")
add_library("Vortex" STATIC "${SOURCES}")
target_precompile_headers(Vortex PRIVATE "Vortex/src/vtxpch.cpp")
# Compiler flags per configuration
target_compile_options(Vortex PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:Dist>:-O3 -DNDEBUG>
)
# Preprocessor definitions per configuration
target_compile_definitions(Vortex PRIVATE
    $<$<CONFIG:Debug>:DEBUG_BUILD>
    $<$<CONFIG:Debug>:VTX_ENABLE_ASSERT>
    $<$<CONFIG:Release>:RELEASE_BUILD>
    $<$<CONFIG:Dist>:DIST_BUILD>
)
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ${CMAKE_PROJECT_NAME}_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Vortex/") 
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ${CMAKE_PROJECT_NAME}_PATH="./${CMAKE_PROJECT_NAME}/") 

target_include_directories(Vortex
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Vortex/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Vortex/vendor/spdlog/include
)
target_link_libraries("Vortex"
    spdlog
    d3d11
    dxgi
)

# Apply MSVC runtime per target
set_property(TARGET Vortex PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_subdirectory(Sandbox)

if (WIN32)
    target_compile_definitions(Vortex PRIVATE VTX_WINDOWS_PLATFORM)
    target_compile_definitions(Sandbox PRIVATE VTX_WINDOWS_PLATFORM)
    message(STATUS "Windows platform")
elseif (APPLE)
    target_compile_definitions(Vortex PRIVATE VTX_APPLE_PLATFORM)
    target_compile_definitions(Sandbox PRIVATE VTX_APPLE_PLATFORM)
    message(STATUS "Apple platform")
elseif (UNIX)
    target_compile_definitions(Sandbox PUBLIC VTX_UNIX_PLATFORM)
    message(STATUS "Unix/Linux platform")
endif()












---------------------------------------

