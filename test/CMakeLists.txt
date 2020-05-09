file(GLOB_RECURSE test_sources "*.cpp")
file(GLOB_RECURSE test_headers "*.h")

add_executable(test_all ${test_sources} ${test_headers})
target_link_libraries(test_all PUBLIC tiralabra_lib gtest)

include(GoogleTest)
file(COPY data DESTINATION .)

add_test(test_all test_all WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})