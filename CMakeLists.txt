cmake_minimum_required(VERSION 3.10.2)
project(mboy_core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DMBOY_DEBUG")

# spdlog
add_subdirectory(deps/spdlog)

# core
include_directories(include)
file(GLOB CORE_SOURCES "src/*/*.cpp", "include/*.h")

# output
add_library(mboy_core STATIC ${CORE_SOURCES})
target_link_libraries(mboy_core spdlog)
target_include_directories(mboy_core PUBLIC include)
