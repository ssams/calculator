cmake_minimum_required (VERSION 2.6)
project (calculator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -Wall")

find_package(Boost REQUIRED COMPONENTS regex)
include_directories(${Boost_INCLUDE_DIRS})

add_executable (calculator main.cpp Parser.cpp Calculator.cpp)
target_link_libraries (calculator ${Boost_LIBRARIES})
