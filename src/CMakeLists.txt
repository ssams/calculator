cmake_minimum_required (VERSION 2.6)
project (calculator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -Wall")

add_executable (calculator main.cpp Expression.cpp Function.cpp Parser.cpp)

