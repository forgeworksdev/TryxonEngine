cmake_minimum_required(VERSION 3.10)
project(Test)

set(CMAKE_CXX_STANDARD 17)

include_directories(include include/math)

# Just compile one file to test
add_executable(Test.x86_64 src/main.cpp)