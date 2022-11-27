project(cpp_junk)

set(CMAKE_MINIMUM_REQUIRED_VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)

add_executable(junk junk.cpp)

add_executable(branchless_compare branchless_compare.cpp)