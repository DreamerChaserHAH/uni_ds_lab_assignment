cmake_minimum_required(VERSION 3.30)
project(Labwork)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(array_implementation src/array_implementation.cpp include/container/array.h include/algorithms/search.h include/algorithms/sort.h)
add_executable(linked_list_implementation src/linked_list_implementation.cpp include/container/linked_list.h include/algorithms/search.h include/algorithms/sort.h)
add_executable(cross_implementation src/cross_implementation.cpp include/container/array.h include/container/linked_list.h include/algorithms/search.h include/algorithms/sort.h)