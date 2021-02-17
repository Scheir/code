cmake_minimum_required(VERSION 3.0.0)
project(proj VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(proj main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_FLAGS "-std=c++17 -stdlib=libc++ -g3 -Wall -O0")
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED)
include(CPack)
