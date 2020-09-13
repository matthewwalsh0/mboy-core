cmake_minimum_required(VERSION 3.10.2)
project(mboy_core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(include)
file(GLOB CORE_SOURCES "src/*/*.cpp", "include/*.h")
add_library(mboy_core STATIC ${CORE_SOURCES})
target_include_directories(mboy_core PUBLIC include)
