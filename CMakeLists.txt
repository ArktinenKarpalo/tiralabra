cmake_minimum_required(VERSION 3.10)

project(tiralabra)

#set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "--coverage -Wall -Wextra -O0 -g -std=c++17")


include_directories("src")

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("extern/googletest")
