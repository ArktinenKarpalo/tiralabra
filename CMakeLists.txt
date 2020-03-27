cmake_minimum_required(VERSION 3.10)

project(tiralabra)

#set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -std=c++17")

#file(GLOB_RECURSE sources "src/*.cpp")
#file(GLOB_RECURSE headers "src/*.h")

include_directories("src")

add_subdirectory("src")
add_subdirectory("test")
add_subdirectory("extern/googletest")

#option(PACKAGE_TESTS "Build the tests" ON)
#if(PACKAGE_TESTS)
#	enable_testing()
#	include(GoogleTest)
#	add_subdirectory(tests)
#endif()

#add_executable(main ${sources} ${headers})

