file(GLOB_RECURSE sources "*.cpp" "*.h")

add_executable(tiralabra_run ${sources})

add_library(tiralabra_lib STATIC ${sources})
