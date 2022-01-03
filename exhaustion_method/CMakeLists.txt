cmake_minimum_required(VERSION 3.20)
project(play_with_algo)

set(CMAKE_CXX_STANDARD 14)

add_executable(play_with_algo  hanoi.cpp)
target_link_libraries(play_with_algo ${CMAKE_THREAD_LIBS_INIT})
