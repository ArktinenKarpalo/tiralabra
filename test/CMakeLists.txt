file(GLOB_RECURSE test_sources "*.cpp")
file(GLOB_RECURSE test_headers "*.h")

add_executable(test ${test_sources} ${test_headers})

add_test(test_all test)
target_link_libraries(test PUBLIC tiralabra_lib gtest)
