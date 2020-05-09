cmake_minimum_required(VERSION 3.10)

project(tiralabra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -march=native")

OPTION(coverage "Code coverage" OFF)
if(coverage)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra --coverage -O0 -g")
endif()

include_directories("src")

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("test_perf")
add_subdirectory("extern/googletest")
