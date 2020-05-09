file(GLOB_RECURSE test_sources "*.cpp")
file(GLOB_RECURSE test_headers "*.h")

add_executable(test_perf ${test_sources} ${test_headers})
target_link_libraries(test_perf PUBLIC tiralabra_lib gtest)

include(GoogleTest)
file(COPY data DESTINATION .)

add_test(test_perf test_perf WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})